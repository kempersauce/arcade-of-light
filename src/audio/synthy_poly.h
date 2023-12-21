#pragma once

#include <Audio.h>
#include <Bounce.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>

#include "audio/constants.h"    // for k*
#include "audio/music_notes.h"  // for notes::*
#include "serial/debug.h"       // for Debug
#include "time/now.h"           // for Now

#define CHORUS_DELAY_LENGTH (16 * AUDIO_BLOCK_SAMPLES)

namespace kss {
namespace audio {
namespace _synthy_poly {

AudioSynthWaveform wave0;
AudioSynthWaveform wave1;
AudioSynthWaveform wave2;
AudioSynthWaveform wave3;
AudioSynthWaveform wave4;
AudioSynthWaveform wave5;

// AudioSynthWaveform lfo1;
// AudioSynthWaveform lfo2;
AudioFilterBiquad filter1;
AudioFilterBiquad filter2;

AudioEffectEnvelope envelope0;
AudioEffectEnvelope envelope1;
AudioEffectEnvelope envelope2;
AudioEffectEnvelope envelope3;
AudioEffectEnvelope envelope4;
AudioEffectEnvelope envelope5;

AudioOutputI2S i2s1;
AudioMixer4 effectMixer;
AudioMixer4 mixer1;
AudioMixer4 mixer2;
AudioMixer4 chorusMixerL;
AudioMixer4 chorusMixerR;
// AudioEffectDelay delay1;

AudioMixer4 mixerChorusL;
AudioMixer4 mixerChorusR;

AudioMixer4 mixerReverbL;
AudioMixer4 mixerReverbR;

AudioMixer4 anotherOne;

AudioMixer4 mixerMasterL;
AudioMixer4 mixerMasterR;

// CHORUS EFFECT
AudioEffectChorus l_chorusEffect;
AudioEffectChorus r_chorusEffect;
AudioEffectFreeverb l_reverb;
AudioEffectFreeverb r_reverb;

AudioConnection patchEnv0(wave0, envelope0);
AudioConnection patchEnv1(wave1, envelope1);
AudioConnection patchEnv2(wave2, envelope2);
AudioConnection patchEnv3(wave3, envelope3);
AudioConnection patchEnv4(wave4, envelope4);
AudioConnection patchEnv5(wave5, envelope5);

AudioConnection patchCord1(envelope1, 0, mixer1, 0);
AudioConnection patchCord2(envelope2, 0, mixer1, 1);
AudioConnection patchCord3(envelope3, 0, mixer1, 2);
AudioConnection patchCord4(envelope4, 0, mixer1, 3);

AudioConnection patchCord0(envelope0, 0, mixer2, 1);
AudioConnection patchCord5(envelope5, 0, mixer2, 0);

AudioConnection patchFilter1(mixer1, 0, filter1, 0);
AudioConnection patchFilter4(mixer2, 0, filter2, 0);

AudioConnection patchChorus0(filter1, l_chorusEffect);
AudioConnection patchChorus1(filter1, r_chorusEffect);

AudioConnection patchChorus2(filter1, 0, mixerChorusL, 0);
AudioConnection patchChorus3(l_chorusEffect, 0, mixerChorusL, 1);
AudioConnection patchChorus4(filter1, 0, mixerChorusR, 0);
AudioConnection patchChorus5(r_chorusEffect, 0, mixerChorusR, 1);

AudioConnection patchReverb3(mixerChorusL, 0, mixerMasterL, 0);
AudioConnection patchReverb4(filter2, 0, mixerMasterL, 1);
AudioConnection patchReverb5(mixerChorusR, 0, mixerMasterR, 0);
AudioConnection patchReverb6(filter2, 0, mixerMasterR, 1);

AudioConnection patchReverb0(mixerMasterL, l_reverb);
AudioConnection patchReverb1(mixerMasterR, r_reverb);

AudioConnection patchReverb7(l_reverb, 0, mixerReverbL, 0);
AudioConnection patchReverb8(mixerMasterL, 0, mixerReverbL, 1);
AudioConnection patchReverb9(r_reverb, 0, mixerReverbR, 0);
AudioConnection patchReverb10(mixerMasterR, 0, mixerReverbR, 1);

AudioConnection patchCordFinalL(mixerReverbL, 0, i2s1, 0);
AudioConnection patchCordFinalR(mixerReverbR, 0, i2s1, 1);

}  // namespace _synthy_poly
using namespace _synthy_poly;

class SynthyPoly {
 public:
  const float Cmajor[4]{notes::C[3], notes::G[3], notes::C[4],
                        notes::E[4]};  // C - E - G
  const float CmajorInversion[4]{notes::E[3], notes::C[4], notes::E[4],
                                 notes::G[4]};
  const float Aminor[4]{notes::A[3], notes::E[4], notes::A[4], notes::C[5]};
  const float AminorInversion[4]{notes::E[3], notes::A[3], notes::C[4],
                                 notes::E[4]};
  const float *chord = Cmajor;

  int8_t chordNum = 0;

  size_t i = 0;
  size_t voiceNum = 4;

  boolean chordOn = false;
  boolean arpOn = false;
  int8_t arpNote = 0;
  int8_t chordVoices = 4;

  uint32_t next_hit = 250;
  uint32_t beat_start;

  int n_chorus = 4;
  short l_delayline[CHORUS_DELAY_LENGTH];
  int s_idx = 2 * CHORUS_DELAY_LENGTH / 4;
  int s_depth = CHORUS_DELAY_LENGTH / 4;
  short r_delayline[CHORUS_DELAY_LENGTH];

  SynthyPoly() { Debug("hello"); };

  const void InitSynth() {
    // set up dat chord
    wave0.frequency(notes::C[2]);
    wave1.frequency(chord[0]);
    wave2.frequency(chord[1]);
    wave3.frequency(chord[2]);
    wave4.frequency(chord[3]);
    wave5.frequency(chord[0] * 2);

    // set up filter
    filter1.setHighpass(0, 800, 0.3);
    filter2.setHighpass(0, 800, 0.3);

    // set up envelopes
    // BASE NOTE
    envelope0.attack(150);
    envelope0.hold(100);
    envelope0.decay(200);
    envelope0.sustain(0.5);
    envelope0.release(200);
    // CHORDS
    envelope1.attack(200);
    envelope1.hold(100);
    envelope1.decay(200);
    envelope1.sustain(0.5);
    envelope1.release(200);

    envelope2.attack(200);
    envelope2.hold(100);
    envelope2.decay(200);
    envelope2.sustain(0.5);
    envelope2.release(200);

    envelope3.attack(200);
    envelope3.hold(100);
    envelope3.decay(200);
    envelope3.sustain(0.5);
    envelope3.release(200);

    envelope4.attack(200);
    envelope4.hold(100);
    envelope4.decay(200);
    envelope4.sustain(0.5);
    envelope4.release(200);
    // ARP
    envelope5.attack(5);
    envelope5.hold(100);
    envelope5.decay(200);
    envelope5.sustain(0.5);
    envelope5.release(200);

    mixer1.gain(3, 0.3);
    mixer1.gain(2, 0.3);
    mixer1.gain(1, 0.3);
    mixer1.gain(0, 0.3);
    mixer2.gain(0, 0.3);
    mixer2.gain(1, 0.3);

    mixerChorusL.gain(0, 0.8);
    mixerChorusL.gain(1, 0.2);  // chorus amount
    mixerChorusR.gain(0, 0.8);
    mixerChorusR.gain(1, 0.2);  // chorus amout

    mixerReverbL.gain(0, 0.);  // reverb
    mixerReverbL.gain(1, 0.3);
    mixerReverbR.gain(0, 0.7);  // reverb
    mixerReverbR.gain(1, 0.3);

    // add effect

    l_chorusEffect.begin(l_delayline, CHORUS_DELAY_LENGTH, n_chorus);

    r_chorusEffect.begin(r_delayline, CHORUS_DELAY_LENGTH, n_chorus);
    if (!r_chorusEffect.begin(r_delayline, CHORUS_DELAY_LENGTH, n_chorus)) {
      Serial.println("AudioEffectChorus - left channel begin failed");
      while (1)
        ;
    }
    l_chorusEffect.voices(n_chorus);
    r_chorusEffect.voices(n_chorus);

    l_reverb.roomsize(0.8);
    l_reverb.damping(0.9);
    r_reverb.roomsize(0.5);
    r_reverb.damping(0.7);

    wave0.begin(1, notes::C[2], WAVEFORM_SQUARE);
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
  void setChord(int8_t newChordNum) {
    chordNum = newChordNum;
    if (chordNum == 0) {
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
    uint32_t now = time::Now();
    if (now - beat_start > next_hit) {
      Debug("Arp Play Note");
      beat_start = now;
      arpNote--;
      if (arpNote < 0) {
        arpNote = chordVoices - 1;
      }
      float note = chord[arpNote] * 2;  // arp will be an octave above chord
      Debug("note: %f", note);
      wave5.frequency(note);
      envelope5.noteOn();
    }
  }

  const void stopArp() {
    arpOn = false;
    Debug("ARP OFF");
    Debug("AUDIO_BLOCK_SAMPLES: " + AUDIO_BLOCK_SAMPLES);
    envelope5.noteOff();
  }

  const void resetArp() { arpNote = chordVoices - 1; }

  const void actionUp() {
    setChord(1);
    resetArp();
    wave0.frequency(notes::G[3]);
    envelope0.noteOn();
  }
  const void stopUp() { envelope0.noteOff(); }
  const void actionDown() {
    setChord(0);
    resetArp();
    wave0.frequency(notes::C[3]);
    envelope0.noteOn();
  }
  const void stopDown() { envelope0.noteOff(); }
  const void actionLeft() {
    setChord(2);
    resetArp();
    wave0.frequency(notes::A[3]);
    envelope0.noteOn();
  }
  const void stopLeft() { envelope0.noteOff(); }
  const void actionRight() {
    setChord(3);
    resetArp();
    wave0.frequency(notes::E[3]);
    envelope0.noteOn();
  }
  const void stopRight() { envelope0.noteOff(); }
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
    beat_start = time::Now() -
                 next_hit;  // so it starts on press and doesn't wait a beat
    playArp();
  }

  const void stopB() { stopArp(); }

};  // class
}  // namespace audio
}  // namespace kss