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
namespace _synthy_poly {


AudioSynthWaveform wave1;
AudioSynthWaveform wave2;
AudioSynthWaveform wave3;
AudioSynthWaveform wave4;
AudioSynthWaveform wave5;

// AudioSynthWaveform lfo1;
// AudioSynthWaveform lfo2;
AudioFilterBiquad filter1;
AudioFilterBiquad filter2;

AudioEffectEnvelope envelope1;
AudioEffectEnvelope envelope2;
AudioEffectEnvelope envelope3;
AudioEffectEnvelope envelope4;
AudioEffectEnvelope envelope5;

AudioOutputI2S i2s1;
AudioMixer4 effectMixer;
AudioMixer4 mixer1;
AudioMixer4 mixer2;
// AudioEffectDelay delay1;   

AudioMixer4 mixerMaster;

// CHORUS EFFECT
AudioEffectChorus l_chorusEffect;
AudioEffectChorus r_chorusEffect;
// Number of samples in each delay line
// #define CHORUS_DELAY_LENGTH (16 * AUDIO_BLOCK_SAMPLES)
// Allocate the delay lines for left and right channels
// short l_delayline[CHORUS_DELAY_LENGTH];
// short r_delayline[CHORUS_DELAY_LENGTH];
// number of "voices" in the chorus which INCLUDES the original voice
// int n_chorus = 5;

AudioConnection patchEnv1(wave1, envelope1);
AudioConnection patchEnv2(wave2, envelope2);
AudioConnection patchEnv3(wave3, envelope3);
AudioConnection patchEnv4(wave4, envelope4);
AudioConnection patchEnv5(wave5, envelope5);

AudioConnection patchCord1(envelope1, 0, mixer1, 0);
AudioConnection patchCord2(envelope2, 0, mixer1, 1);
AudioConnection patchCord3(envelope3, 0, mixer1, 2);
AudioConnection patchCord4(envelope4, 0, mixer1, 3);

AudioConnection patchCord5(envelope5, 0, mixer2, 0);

AudioConnection patchFilter1(mixer1, 0, filter1, 0);
// AudioConnection patchFilter2(lfo1, 0, filter1, 1);
// AudioConnection patchFilter3(lfo2, 0, filter1, 2);
AudioConnection patchFilter4(mixer2, 0, filter2, 0);


// AudioConnection patchEnv1(filter1, 0, envelope, 0);

AudioConnection patchMaster1(filter1, 0, mixerMaster, 0);
AudioConnection patchMaster2(filter2, 0, mixerMaster, 1);

AudioConnection patchCordFinalL(mixerMaster, 0, i2s1, 0);
AudioConnection patchCordFinalR(mixerMaster, 0, i2s1, 1);


}  // namespace _synthy_poly
using namespace _synthy_poly;

class SynthyPoly {
 public:
  const float Cmajor[4] {notes::C[3], notes::G[3], notes::C[4], notes::E[4]};  // C - E - G
  const float CmajorInversion[4] {notes::E[3], notes::C[4], notes::E[4], notes::G[4]};
  const float Aminor[4] {notes::A[3], notes::E[4], notes::A[4], notes::C[5]};
  const float AminorInversion[4] {notes::E[3], notes::A[3], notes::C[4], notes::E[4]};
  float *chord = Cmajor;

  int8_t chordNum = 0;

  size_t i = 0;
  size_t voiceNum = 4;

  boolean chordOn = false;
  boolean arpOn = false;
  int8_t arpNote = 0;
  int8_t chordVoices = 4;

  uint32_t next_hit = 200;
  uint32_t beat_start;



  SynthyPoly() { Debug("hello"); };

  const void InitSynth() {
    InitAudio();

    // Comment these out if not using the audio adaptor board.
    // This may wait forever if the SDA & SCL pins lack
    // pullup resistors
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.8);  // caution: very loud - use oscilloscope only!

    // set up dat chord
    wave1.frequency(chord[0]);
    wave2.frequency(chord[1]);
    wave3.frequency(chord[2]);
    wave4.frequency(chord[3]);
    wave5.frequency(chord[0]*2);


    // set up filter
    filter1.setHighpass(0, 800, 0.3);
    filter2.setHighpass(0, 800, 0.3);



    // set up envelopes
    envelope1.attack(1);
    envelope1.hold(100);
    envelope1.decay(200);
    envelope1.sustain(0.5);
    envelope1.release(200);

    envelope2.attack(1);
    envelope2.hold(100);
    envelope2.decay(200);
    envelope2.sustain(0.5);
    envelope2.release(200);

    envelope3.attack(1);
    envelope3.hold(100);
    envelope3.decay(200);
    envelope3.sustain(0.5);
    envelope3.release(200);

    envelope4.attack(1);
    envelope4.hold(100);
    envelope4.decay(200);
    envelope4.sustain(0.5);
    envelope4.release(200);

    envelope5.attack(1);
    envelope5.hold(100);
    envelope5.decay(200);
    envelope5.sustain(0.5);
    envelope5.release(200);

    mixer1.gain(3, 0.5); 
    mixer1.gain(2, 0.5);
    mixer1.gain(1, 0.5); 
    mixer1.gain(0, 0.5);
    mixer2.gain(0,0.7);
    // lfo1.frequency(0.2);
    // lfo1.amplitude(0.99);
    // lfo1.phase(270);
    // lfo1.begin(WAVEFORM_TRIANGLE);
    // lfo2.frequency(0.07);
    // lfo2.amplitude(0.55);
    // lfo2.phase(270);
    // lfo2.begin(WAVEFORM_SINE);
    // add effect
    // l_chorusEffect.voices(n_chorus);
    // r_chorusEffect.voices(n_chorus);

    wave1.begin(1, Cmajor[0], WAVEFORM_BANDLIMIT_SAWTOOTH);
    wave2.begin(1, Cmajor[1], WAVEFORM_BANDLIMIT_SAWTOOTH);
    wave3.begin(1, Cmajor[2], WAVEFORM_BANDLIMIT_SAWTOOTH);
    wave4.begin(1, Cmajor[3], WAVEFORM_BANDLIMIT_SAWTOOTH);
    wave5.begin(1, Cmajor[0], WAVEFORM_BANDLIMIT_SAWTOOTH);


    Debug("setup done");
    AudioProcessorUsageMaxReset();
    AudioMemoryUsageMaxReset();
  }

  // Method to play next note in sequence (may want to pass in sequence here?)
  const void setChord(int8_t newChordNum) {
    chordNum = newChordNum;
    if(chordNum == 0) {
      chord = Cmajor;
    } else if (chordNum == 1) {
      chord = CmajorInversion;
    } else if (chordNum == 2) {
      chord = Aminor;
    } else if (chordNum == 3) {
      chord = AminorInversion;
    }
    wave1.frequency(chord[0]);
    wave2.frequency(chord[1]);
    wave3.frequency(chord[2]);
    wave4.frequency(chord[3]);
  }

  const void playChord() {
    if (chordOn) {
      envelope1.noteOn();
      envelope2.noteOn();
      envelope3.noteOn();
      envelope4.noteOn();
    } else {
      envelope1.noteOff();
      envelope2.noteOff();
      envelope3.noteOff();
      envelope4.noteOff();
    }
  }

  const void playArp() {
    uint32_t now = millis();
    if(now - beat_start > next_hit) {
      Debug("Arp Play Note");
      beat_start = now;
      arpNote--;
      if (arpNote < 0) {
        arpNote = chordVoices - 1;
      }
      float note = chord[arpNote] * 2; //arp will be an octave above chord
      Debug("note: " + note);
      wave5.frequency(note);
      envelope5.noteOn();
    } 
  }

  const void stopArp() {
    arpOn = false;
    Debug("ARP OFF");
    envelope5.noteOff();
  }

  const void resetArp() {
    arpNote = chordVoices - 1;
  }

  const void actionUp() {
    setChord(1);
    resetArp();
  }  
  const void actionDown() {
    setChord(0);
    resetArp();
  }  
  const void actionLeft() {
    setChord(2);
    resetArp();
  }  
  const void actionRight() {
    setChord(3);
    resetArp();
  }  
  const void actionA() {
    chordOn = true;
    playChord();
  } 

  const void stopA() {
    chordOn = false;
    playChord();  
  }

  const void actionB() {
    arpOn = true;
    Debug("Arp turned ON");
    beat_start = millis();   
    playArp();
  }  

  const void stopB() {
    stopArp();
  }

};  // class
}  // namespace audio
}  // namespace kss