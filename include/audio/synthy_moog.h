#pragma once

#include <Audio.h>
#include <Bounce.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <synth_simple_drum.h>
#include <synth_whitenoise.h>
#include <math/random.h>

#include "audio/constants.h"    // for k*
#include "audio/music_notes.h"  // for notes::*
#include "audio/sounds.h"       // for InitAudio
#include "serial/debug.h"       // for Debug
#include "audio/music_notes.h"  // for notes

namespace kss {
namespace audio {
namespace moog {


AudioSynthWaveform       waveform1;
AudioSynthWaveform       waveform2;
AudioSynthWaveform       waveform3;
AudioMixer4              mixer1;
AudioFilterLadder        filter1;
AudioSynthWaveform       lfo1;
AudioSynthWaveform       lfo2;
AudioOutputI2S           i2s1;

AudioControlSGTL5000     sgtl5000_1;

AudioConnection patchCord1(waveform1, 0, mixer1, 0);
AudioConnection patchCord2(waveform2, 0, mixer1, 1);
AudioConnection patchCord3(waveform3, 0, mixer1, 2);
AudioConnection patchCord4(mixer1, 0, filter1, 0);
AudioConnection patchCord5(lfo1, 0, filter1, 1);
AudioConnection patchCord6(lfo2, 0, filter1, 2);
AudioConnection patchCord7(filter1, 0, i2s1, 0);
AudioConnection patchCord8(filter1, 0, i2s1, 1);



class MoogSynthy {

    // float sequence[6] = {notes::C[2], notes::Eb[2], notes::F[2], notes::Fs[2], notes::G[2], notes::Bb[2]};  //C BLUES
    float sequence[6] = {notes::C[2], notes::D[2], notes::E[2], notes::G[2], notes::A[2], notes::C[3]};



    public:

    MoogSynthy() {Debug("luv u Bob");}
    float theSauce[5] = {-0.2, -0.3, 0.2, 0.5, 0.1};
    const float koffNote = 999;
    float notesPressed[3] = {koffNote, koffNote, koffNote};

    const void InitMoogSynthy() {
      InitAudio();
      sgtl5000_1.enable();
      sgtl5000_1.volume(0.8);
  
      filter1.resonance(0.55);    // "lfo2" waveform overrides this setting
      filter1.frequency(800);     // "lfo1" modifies this 800 Hz setting
      filter1.octaveControl(2.6); // up 2.6 octaves (4850 Hz) & down 2.6 octaves (132 Hz)
      waveform1.frequency(50);
      waveform2.frequency(100.1);
      waveform3.frequency(150.3);
      waveform1.amplitude(0.3);
      waveform2.amplitude(0.3);
      waveform3.amplitude(0.3);
      waveform1.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
      waveform2.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
      waveform3.begin(WAVEFORM_BANDLIMIT_SAWTOOTH);
      lfo1.frequency(0.2);
      lfo1.amplitude(0.99);
      lfo1.phase(270);
      lfo1.begin(WAVEFORM_TRIANGLE);
      lfo2.frequency(0.07);
      lfo2.amplitude(0.55);
      lfo2.phase(270);
      lfo2.begin(WAVEFORM_SINE);
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
        
        waveform1.amplitude(1);
        waveform2.amplitude(1);
        waveform3.amplitude(1);
      }
    }

    const float plusOctave(float baseFrequency) {
      float analogSauce = math::random::Float(-0.7,0.7);
      return (baseFrequency * 2) + analogSauce;
    }

    const float plusTwoOctaves(float baseFrequency) {
      float analogSauce = math::random::Float(-0.7,0.7);
      return (baseFrequency * 4) + analogSauce;
    }

    const void stopNote() {
      waveform1.amplitude(0);
      waveform2.amplitude(0);
      waveform3.amplitude(0);
    }

    const void setFrequencies(float frequency) {
      waveform1.frequency(frequency);
      waveform2.frequency(plusOctave(frequency));
      waveform3.frequency(plusTwoOctaves(frequency));
    }

    // low note priority for monosynth
    const float getFrequency() {
      float frequency = notesPressed[0];
      if (notesPressed [1] < frequency) {
        frequency = notesPressed[1];
      }
      if (notesPressed[2] < frequency) {
        frequency = notesPressed[2];
      }
      return frequency;
    }

    const void actionUp() {
      notesPressed[1] = sequence[3];
      playNote();
    }

    const void actionDown() {
      notesPressed[1] = sequence[1];
      playNote();
    }

    const void actionLeft() {
      notesPressed[1] = sequence[2];
      playNote();
    }

    const void actionRight() {
      notesPressed[1] = sequence[4];
      playNote();
    }

    const void actionA() {
      notesPressed[0] = sequence[0];
      playNote();
    }

    const void actionB() {
      notesPressed[2] = sequence[5];
      playNote();
    }

    const void stopJoystick() {
      notesPressed[1] = koffNote;
      playNote();
    }

    const void stopA() {
      notesPressed[0] = koffNote;
      playNote();
    }

        const void stopB() {
      notesPressed[2] = koffNote;
      playNote();
    }

}; // class

} // namespace moog
} // namespace audio
} // namespace kss