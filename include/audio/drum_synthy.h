#pragma once

#include <Audio.h>
#include <Bounce.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <synth_simple_drum.h>
#include <synth_whitenoise.h>

#include "audio/constants.h"    // for k*
#include "audio/music_notes.h"  // for notes::*
#include "serial/debug.h"       // for Debug

namespace kss {
namespace audio {
namespace _synthy {

AudioSynthSimpleDrum drum2;  // xy=399,244
AudioSynthSimpleDrum drum3;  // xy=424,310
AudioSynthSimpleDrum drum1;  // xy=431,197
AudioSynthSimpleDrum drum4;  // xy=464,374
AudioSynthSimpleDrum drum5;
AudioSynthSimpleDrum drum6;
AudioSynthNoiseWhite noise1;
AudioSynthNoiseWhite noise2;
AudioMixer4 mixer1;  // xy=737,265
AudioMixer4 mixer2;
AudioMixer4 mixer3;
AudioMixer4 mixerMain;
AudioOutputI2S i2s1;  // xy=979,214
AudioConnection patchCord1(drum2, 0, mixer1, 1);
AudioConnection patchCord2(drum3, 0, mixer1, 2);
AudioConnection patchCord3(drum1, 0, mixer1, 0);
AudioConnection patchCord4(drum4, 0, mixer1, 3);
AudioConnection patchCord5(drum5, 0, mixer2, 0);
// AudioConnection patchCord6(noise1, 0, mixer2, 1);
AudioConnection patchCord7(drum6, 0, mixer3, 0);
// AudioConnection patchCord8(noise2, 0, mixer3, 1);
AudioConnection patchCordMixer1_1(mixer1, 0, mixerMain, 0);
AudioConnection patchCordMixer1_2(mixer1, 0, mixerMain, 1);
AudioConnection patchCordMixer2_1(mixer2, 0, mixerMain, 2);
AudioConnection patchCordMixer3_1(mixer3, 0, mixerMain, 3);
AudioConnection patchCordMain1(mixerMain, 0, i2s1, 0);
AudioConnection patchCOrdMain2(mixerMain, 0, i2s1, 1);

class DrumSynthy {
 public:
  DrumSynthy() { Debug("hello"); };

  void InitDrumSynth() {
    drum1.frequency(60);
    drum1.length(1500);
    drum1.secondMix(0.0);
    drum1.pitchMod(0.55);

    drum2.frequency(60);
    drum2.length(300);
    drum2.secondMix(0.0);
    drum2.pitchMod(1.0);

    drum3.frequency(550);
    drum3.length(400);
    drum3.secondMix(1.0);
    drum3.pitchMod(0.5);

    drum4.frequency(1200);
    drum4.length(150);
    drum4.secondMix(0.0);
    drum4.pitchMod(0.0);

    drum5.frequency(1200);
    drum5.length(150);
    drum5.secondMix(0.0);
    drum5.pitchMod(0.0);

    noise1.amplitude(0.5);

    drum6.frequency(1200);
    drum6.length(150);
    drum6.secondMix(0.0);
    drum6.pitchMod(0.0);

    noise2.amplitude(1.0);

    AudioInterrupts();
  }

  const void playDrum1() { drum1.noteOn(); }

  const void playDrum2() { drum2.noteOn(); }

  const void playDrum3() { drum3.noteOn(); }

  const void playDrum4() { drum4.noteOn(); }

  const void playDrum5() { drum5.noteOn(); }

  const void playDrum6() { drum6.noteOn(); }

};  // class

}  // namespace _synthy
}  // namespace audio
}  // namespace kss