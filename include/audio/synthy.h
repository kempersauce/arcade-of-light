#pragma once

#include <Audio.h>
#include <Bounce.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>

#include "audio/constants.h"    // for k*
#include "audio/music_notes.h"  // for notes::*
#include "audio/sounds.h"       // for InitAudio
#include "serial/debug.h"       // for Debug

namespace kss {
namespace audio {
namespace _synthy {

struct Envelope {
  AudioSynthWaveform wave;
  AudioFilterBiquad filter;
  AudioEffectEnvelope envelope;

  AudioConnection patch_wave_out;
  AudioConnection patch_filter_out;

  float frequency;
  float frequencyOffset;

  Envelope()
      : patch_wave_out{wave, 0, filter, 0},
        patch_filter_out{filter, 0, envelope, 0} {
    // Set up wave
    wave.begin(1, notes::C[4], WAVEFORM_SQUARE);

    // set up filter
    filter.setLowpass(0, 800, 0.707);

    // set up envelope
    envelope.attack(1);
    envelope.hold(100);
    envelope.decay(200);
    envelope.sustain(0.5);
    envelope.release(200);
  }

  void setFrequency(float newFrequency) {
    frequency = newFrequency;
    wave.frequency(frequency + frequencyOffset);
  }

  void setOffset(float newOffset) {
    frequencyOffset = newOffset;
    wave.frequency(frequency + frequencyOffset);
  }

  uint32_t bendStartTime;
  boolean bendStarted = false;
  float bendSlope;
  float bendLength = 1000;
  float bendMax;
  boolean bendUp;

  const void pitchBend() {
    const uint32_t now = millis();
    const uint32_t timePassed = now - bendStartTime;
    float newOffset = bendSlope * timePassed;
    Debug(newOffset);
    if (bendUp && newOffset > bendMax) {
      newOffset = bendMax;
      Debug(newOffset);

    } 
    if (!bendUp && newOffset < bendMax) {
      newOffset = -bendMax;
      Debug("downshift bendMax exceeded");
      Debug(newOffset);

    }

    setOffset(newOffset);
  }

  const void adjustPitchBend(float frequency) {
    Debug("adjusting Bend by");
    Debug(bendUp);
    if(bendUp) {
      bendMax = frequency * 2;
      Debug("new max set");
      Debug(bendMax);

    } else {
      bendMax = frequency / 2;
      Debug("new max set");
      Debug(bendMax);

    }
  }

  const void pitchBendStart(float frequency, boolean isUp = true) {
    // calculate max range
    // figure out linear formula
    if (!bendStarted) {
      bendStarted = true;
      bendStartTime = millis();
      bendUp = isUp;
      if(bendUp) {
        bendSlope = frequency / bendLength;
        // set for an octave currently
        bendMax = frequency;
      } else {
        bendSlope = - (frequency/2) / bendLength;
        // set for an octave currently
        bendMax = frequency/2;
      }
      
    }
    const uint32_t now = millis();
    const uint32_t timePassed = now - bendStartTime;
    Debug("==================================");
    Debug("bendslope:  ");
    Debug(bendSlope);
    Debug(bendSlope * timePassed);
    Debug(bendMax);
    // remove next line when broken out
    setOffset(bendSlope * timePassed);

    // may want to change this to return just the offset not the final frequency
    // return bendSlope * timePassed + frequency;
  }

  const void pitchBendStop() {
    bendStarted = false;
    setOffset(0);
  }
};

Envelope waveforms[6];
AudioOutputI2S i2s1;  // xy=360,98 PAUL SHIT
AudioMixer4 effectMixer;
AudioMixer4 mixer1;
AudioMixer4 mixer2;
AudioEffectFreeverb freeverb1;

AudioMixer4 mixerMaster;

// CHORUS EFFECT
AudioEffectChorus l_chorusEffect;
AudioEffectChorus r_chorusEffect;
// Number of samples in each delay line
#define CHORUS_DELAY_LENGTH (16 * AUDIO_BLOCK_SAMPLES)
// Allocate the delay lines for left and right channels
short l_delayline[CHORUS_DELAY_LENGTH];
short r_delayline[CHORUS_DELAY_LENGTH];
// number of "voices" in the chorus which INCLUDES the original voice
int n_chorus = 5;

// only send moving note to chorus effect
// AudioConnection patchCordChorusL(waveforms[0].envelope, 0, l_chorusEffect,
// 0); AudioConnection patchCordChorusR(waveforms[0].envelope, 0,
// mixer for first two waves
AudioConnection patchCordRawWave1L(waveforms[0].envelope, 0, mixer2, 0);
AudioConnection patchCordRawWave1R(waveforms[0].envelope, 0, mixer2, 1);
AudioConnection patchCordRawWave2L(waveforms[1].envelope, 0, mixer2, 2);
AudioConnection patchCordRawWave2R(waveforms[1].envelope, 0, mixer2, 3);
// mixer1 - input from other 4
AudioConnection patchCordRawWave3(waveforms[2].envelope, 0, mixer1, 0);
AudioConnection patchCordRawWave4(waveforms[3].envelope, 0, mixer1, 1);
AudioConnection patchCordRawWave5(waveforms[4].envelope, 0, mixer1, 2);
AudioConnection patchCordRawWave6(waveforms[5].envelope, 0, mixer1, 3);
// EffectMixer - add reverb
AudioConnection patchCordEffect1(mixer1, 0, effectMixer, 0);
AudioConnection patchCordEffect2(mixer2, 0, effectMixer, 1);
AudioConnection patchCordEffect3(freeverb1, 0, effectMixer, 3);
// MasterMix - put it all togeteher
AudioConnection patchCordMaster(effectMixer, 0, mixerMaster, 0);




// final output
AudioConnection patchCord1(mixerMaster, 0, i2s1, 0);
AudioConnection patchCord2(mixerMaster, 0, i2s1, 1);

}  // namespace _synthy
using namespace _synthy;

class Synthy {
 public:
  // NOTE REFERENCE: https://pages.mtu.edu/~suits/notefreqs.html
  float sequence[5] = {220, 329.63, 369.99, 554.37, 830.61};
  uint32_t next_hit = 0;
  uint8_t current_note = sequence[0];
  unsigned long last_time = millis();

  size_t i = 0;

  Synthy() { Debug("hello"); };

  const void InitSynth() {
    InitAudio();

    // Comment these out if not using the audio adaptor board.
    // This may wait forever if the SDA & SCL pins lack
    // pullup resistors
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.8);  // caution: very loud - use oscilloscope only!

    // set up dat chord
    for (size_t i = 0; i < 5; ++i) {
      waveforms[i].wave.frequency(sequence[i]);
    }

    // waveforms[0].begin(WAVEFORM_SINE);

    // Initialize the effect - left channel
    // address of delayline
    // total number of samples in the delay line
    // number of voices in the chorus INCLUDING the original voice
    if (!l_chorusEffect.begin(l_delayline, CHORUS_DELAY_LENGTH, n_chorus)) {
      Debug("AudioEffectChorus - left channel begin failed");
      while (1)
        ;
    }

    // Initialize the effect - right channel
    // address of delayline
    // total number of samples in the delay line
    // number of voices in the chorus INCLUDING the original voice
    if (!r_chorusEffect.begin(r_delayline, CHORUS_DELAY_LENGTH, n_chorus)) {
      Debug("AudioEffectChorus - right channel begin failed");
      while (1)
        ;
    }

    effectMixer.gain(0, 0.1); //percent "wet" reverb
    effectMixer.gain(1, 0.9); // percent "dry" reverb

    // add effect
    l_chorusEffect.voices(n_chorus);
    r_chorusEffect.voices(n_chorus);

    Debug("setup done");
    AudioProcessorUsageMaxReset();
    AudioMemoryUsageMaxReset();
  }

  // Method to play next note in sequence (may want to pass in sequence here?)
  const float playSequence() {
    const uint32_t now = millis();
    // if (now >= next_hit) {
    // do it
    if (i == 4) {
      i = 0;
    } else {
      i++;
    }
    // }
    // next_hit = now + 500;
    return sequence[i];
  }

  const float reverseSequence() {
    const uint32_t now = millis();
    // if (now >= next_hit) {
    // do it
    if (i == 0) {
      i = 4;
    } else {
      i--;
    }
    // }
    // next_hit = now + 500;
    return sequence[i];
  }

  const void actionUp() {

  }  
  const void actionDown() {
  }  
  const void actionLeft() {
  }  
  const void actionRight() {
  }  
  const void actionA() {
    float pitch = reverseSequence();
  }  
  const void actionB() {
    float pitch = playSequence();
  }  

};  // class
}  // namespace audio
}  // namespace kss