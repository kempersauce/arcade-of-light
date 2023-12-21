#pragma once

#include <Audio.h>
#include <Bounce.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <math/random.h>
#include <synth_simple_drum.h>
#include <synth_whitenoise.h>

#include "audio/constants.h"    // for k*
#include "audio/music_notes.h"  // for notes::*
#include "audio/music_notes.h"  // for notes
#include "serial/debug.h"       // for Debug

namespace kss {
namespace audio {
namespace moog {

AudioSynthWaveform waveform1;
AudioSynthWaveform waveform2;
AudioSynthWaveform waveform3;
AudioMixer4 mixer1;
AudioFilterLadder filter1;
AudioSynthWaveform lfo1;
AudioSynthWaveform lfo2;

AudioEffectEnvelope envelope1;
AudioEffectEnvelope envelope2;
AudioEffectEnvelope envelope3;
AudioMixer4 envelopeMixer;
AudioEffectFreeverb reverb;
AudioMixer4 reverbMixer;
AudioOutputI2S i2s1;

AudioConnection patchCord1(waveform1, 0, envelope1, 0);
AudioConnection patchCord2(waveform2, 0, envelope2, 0);
AudioConnection patchCord3(waveform3, 0, envelope3, 0);

AudioConnection patchCordEnvelope0(envelope1, 0, envelopeMixer, 0);
AudioConnection patchCordEnvelope1(envelope2, 0, envelopeMixer, 1);
AudioConnection patchCordEnvelope2(envelope3, 0, envelopeMixer, 2);

AudioConnection patchCord4(envelopeMixer, 0, filter1, 0);
AudioConnection patchCord5(lfo1, 0, filter1, 1);
AudioConnection patchCord6(lfo2, 0, filter1, 2);
AudioConnection patchCordReverb(filter1, reverb);
AudioConnection patchCordReverbMix0(reverb, 0, reverbMixer, 0);
AudioConnection patchCordReverbMix1(filter1, 0, reverbMixer, 1);
AudioConnection patchCord7(filter1, 0, i2s1, 0);
AudioConnection patchCord8(filter1, 0, i2s1, 1);

class MoogSynthy {
  // float sequence[6] = {notes::C[2], notes::Eb[2], notes::F[2], notes::Fs[2],
  // notes::G[2], notes::Bb[2]};  //C BLUES
  float sequence[6] = {notes::C[2], notes::D[2], notes::E[2],
                       notes::G[2], notes::A[2], notes::C[3]};

 public:
  MoogSynthy() { Debug("luv u Bob"); }
  float theSauce[5] = {-0.2, -0.3, 0.2, 0.5, 0.1};
  const float koffNote = 999;
  float notesPressed[3] = {koffNote, koffNote, koffNote};

  float attack = 50;
  float hold = 100;
  float decay = 200;
  float sustain = 0.5;
  float release = 800;

  const void InitMoogSynthy() {
    filter1.resonance(0.55);  // "lfo2" waveform overrides this setting
    filter1.frequency(800);   // "lfo1" modifies this 800 Hz setting
    filter1.octaveControl(
        2.6);  // up 2.6 octaves (4850 Hz) & down 2.6 octaves (132 Hz)
    waveform1.frequency(50);
    waveform2.frequency(100.1);
    waveform3.frequency(150.3);
    waveform1.amplitude(0.7);
    waveform2.amplitude(0.7);
    waveform3.amplitude(0.7);
    waveform1.begin(WAVEFORM_BANDLIMIT_SQUARE);
    waveform2.begin(WAVEFORM_BANDLIMIT_SQUARE);
    waveform3.begin(WAVEFORM_BANDLIMIT_SQUARE);
    waveform1.pulseWidth(0.3);
    waveform2.pulseWidth(0.3);
    waveform3.pulseWidth(0.3);

    lfo1.frequency(0.2);
    lfo1.amplitude(0.5);
    lfo1.phase(270);
    lfo1.begin(WAVEFORM_TRIANGLE);
    lfo2.frequency(0.02);
    lfo2.amplitude(0.7);
    lfo2.phase(270);
    lfo2.begin(WAVEFORM_SINE);
    // set up envelope
    envelope1.attack(attack);
    envelope1.hold(hold);
    envelope1.decay(decay);
    envelope1.sustain(sustain);
    envelope1.release(release);
    envelope2.attack(attack);
    envelope2.hold(hold);
    envelope2.decay(decay);
    envelope2.sustain(sustain);
    envelope2.release(release);
    envelope3.attack(attack);
    envelope3.hold(hold);
    envelope3.decay(decay);
    envelope3.sustain(sustain);
    envelope3.release(release);
    reverbMixer.gain(0, 0.5);  // Reverb "wet"
    reverbMixer.gain(0, 0.5);  // Reverb "dry"
    reverb.roomsize(0.8);
    reverb.damping(0.9);
  }

  const void playNote() {
    Serial.print("Filter CPU Usage: ");
    Serial.print(filter1.processorUsageMax());
    Serial.print("%, Total CPU Usage: ");
    Serial.print(AudioProcessorUsageMax());
    Serial.println("%");
    filter1.processorUsageMaxReset();
    AudioProcessorUsageMaxReset();
    float frequency = getFrequency();
    if (frequency == koffNote) {
      stopNote();
    } else {
      setFrequencies(frequency);

      envelope1.noteOn();
      envelope2.noteOn();
      envelope3.noteOn();
    }
  }

  const float plusOctave(float baseFrequency) {
    float analogSauce = math::random::Float(-0.7, 0.7);
    return (baseFrequency * 2) + analogSauce;
  }

  const float plusTwoOctaves(float baseFrequency) {
    float analogSauce = math::random::Float(-0.7, 0.7);
    return (baseFrequency * 4) + analogSauce;
  }

  const void stopNote() {
    // waveform1.amplitude(0);
    // waveform2.amplitude(0);
    // waveform3.amplitude(0);
    envelope1.noteOff();
    envelope2.noteOff();
    envelope3.noteOff();
  }

  const void setFrequencies(float frequency) {
    waveform1.frequency(frequency);
    waveform2.frequency(plusOctave(frequency));
    waveform3.frequency(plusTwoOctaves(frequency));
  }

  // low note priority for monosynth
  const float getFrequency() {
    float frequency = notesPressed[0];
    if (notesPressed[1] < frequency) {
      frequency = notesPressed[1];
    }
    if (notesPressed[2] < frequency) {
      frequency = notesPressed[2];
    }
    return frequency;
  }

  uint32_t next_hit = 250;
  uint32_t beat_start;
  uint32_t chug_note_start;
  uint32_t chug_note_len = 100;
  float chug_frequency = sequence[0];

  boolean isChuggit = false;

  const void chug() {
    float note = chug_frequency;
    uint32_t now = time::Now();
    if (isChuggit && now - beat_start > next_hit) {
      chug_note_start = now;
      Debug("chuggin");
      beat_start = now;
      setFrequencies(note);

      playNote();
    } else if (isChuggit && now - chug_note_start > chug_note_len) {
      stopNote();
    }
  }

  const void startChug() {
    uint32_t now = time::Now();
    if (!isChuggit) {
      isChuggit = true;
      beat_start = now - next_hit;
      chug_note_start = now;
    }
  }

  const void stopChug() {
    isChuggit = false;
    stopNote();
  }

  const void setChugFrequency(float frequency) { chug_frequency = frequency; }

  const void actionUp() {
    notesPressed[1] = sequence[3];
    playNote();
    // playNote(sequence[3]);
    // setChugFrequency(sequence[3]);
  }

  const void actionDown() {
    notesPressed[1] = sequence[1];
    playNote();
    // playNote(sequence[1]);
    // setChugFrequency(sequence[1]);
  }

  const void actionLeft() {
    notesPressed[1] = sequence[2];
    playNote();
    // playNote(sequence[2]);
    // setChugFrequency(sequence[2]);
  }

  const void actionRight() {
    notesPressed[1] = sequence[4];
    playNote();
    // playNote(sequence[4]);
    // setChugFrequency(sequence[4]);
  }

  const void actionA() {
    notesPressed[0] = sequence[0];
    playNote();
    // playNote(sequence[0]);
    // setChugFrequency(sequence[0]);
  }

  const void actionB() {
    notesPressed[2] = sequence[5];
    playNote();
    // playNote(sequence[5]);
  }

  const void stopJoystick() {
    notesPressed[1] = koffNote;
    playNote();
    // stopNote();
  }

  const void stopA() {
    notesPressed[0] = koffNote;
    playNote();
    // stopNote();
  }

  const void stopB() {
    notesPressed[2] = koffNote;
    playNote();
    // stopNote();
  }

};  // class

}  // namespace moog
}  // namespace audio
}  // namespace kss