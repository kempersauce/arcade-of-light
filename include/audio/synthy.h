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

  Envelope()
      : patch_wave_out{wave, 0, filter, 0},
        patch_filter_out{filter, 0, envelope, 0} {
    // Set up wave
    wave.begin(1, notes::C[4], WAVEFORM_SINE);

    // set up filter
    filter.setLowpass(0, 800, 0.707);

    // set up envelope
    envelope.attack(1);
    envelope.hold(100);
    envelope.decay(200);
    envelope.sustain(0.5);
    envelope.release(200);
  }
};

Envelope waveforms[6];
AudioOutputI2S i2s1;  // xy=360,98 PAUL SHIT
AudioMixer4 effectMixer;
AudioMixer4 mixer1;
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
AudioConnection patchCordChorusL(waveforms[0].envelope, 0, l_chorusEffect, 0);
AudioConnection patchCordChorusR(waveforms[0].envelope, 0, r_chorusEffect, 0);
// Effects Mixer
AudioConnection patchCordChorusLOut(l_chorusEffect, 0, effectMixer, 0);
AudioConnection patchCordChorusROut(r_chorusEffect, 0, effectMixer, 1);
AudioConnection patchCordRawWave2L(waveforms[1].envelope, 0, effectMixer, 2);
AudioConnection patchCordRawWave2R(waveforms[1].envelope, 0, effectMixer, 3);
// mixer1 - input from other 4
AudioConnection patchCordRawWave3(waveforms[2].envelope, 0, mixer1, 0);
AudioConnection patchCordRawWave4(waveforms[3].envelope, 0, mixer1, 1);
AudioConnection patchCordRawWave5(waveforms[4].envelope, 0, mixer1, 2);
AudioConnection patchCordRawWave6(waveforms[5].envelope, 0, mixer1, 3);
// mixerMaster - put it all togeter
AudioConnection patchCordMaster1(mixer1, 0, mixerMaster, 0);
AudioConnection patchCordMaster2(effectMixer, 0, mixerMaster, 1);

// final output
AudioConnection patchCord1(mixerMaster, 0, i2s1, 0);
AudioConnection patchCord2(mixerMaster, 0, i2s1, 1);

}  // namespace _synthy
using namespace _synthy;

class Synthy {
 public:
  // NOTE REFERENCE: https://pages.mtu.edu/~suits/notefreqs.html
  float sequence[4] = {256, 311.13, 369.99, 554.37};
  uint32_t next_hit = 0;
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
    for (size_t i = 0; i < 6; ++i) {
      waveforms[i].wave.frequency(notes::C_Pentatonic[i]);
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

    effectMixer.gain(0, 0.5);
    effectMixer.gain(1, 0.5);

    // add effect
    l_chorusEffect.voices(n_chorus);
    r_chorusEffect.voices(n_chorus);

    Debug("setup done");
    AudioProcessorUsageMaxReset();
    AudioMemoryUsageMaxReset();
  }

};  // class
}  // namespace audio
}  // namespace kss