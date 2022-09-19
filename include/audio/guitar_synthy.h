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
#include "audio/sounds.h"       // for InitAudio
#include "serial/debug.h"       // for Debug

namespace kss {
namespace audio {
namespace _guitar {

AudioSynthKarplusStrong string1;
AudioSynthKarplusStrong string2;
AudioSynthKarplusStrong string3;
AudioSynthKarplusStrong string4;
AudioSynthKarplusStrong string5;
AudioSynthKarplusStrong string6;
AudioMixer4 mixer1;
AudioMixer4 mixer2;
AudioOutputI2S i2s1;
AudioConnection patchCord1(string1, 0, mixer1, 0);
AudioConnection patchCord2(string2, 0, mixer1, 1);
AudioConnection patchCord3(string3, 0, mixer1, 2);
AudioConnection patchCord4(string4, 0, mixer1, 3);
AudioConnection patchCord5(mixer1, 0, mixer2, 0);
AudioConnection patchCord6(string5, 0, mixer2, 1);
AudioConnection patchCord7(string6, 0, mixer2, 2);
AudioConnection patchCord8(mixer2, 0, i2s1, 0);
AudioConnection patchCord9(mixer2, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;

class GuitarSynthy {
 public:
  const float Cmajor[6] = {82.41,  130.81, 164.81,
                           196.00, 261.63, 329.63};  // C - E - G

  GuitarSynthy() { Debug("hello"); };

  void InitGuitarSynth() {
    // put your setup code here, to run once:

    Serial.begin(115200);

    // audio library init
    InitAudio();

    sgtl5000_1.enable();
    sgtl5000_1.volume(0.6);
    mixer1.gain(0, 0.15);
    mixer1.gain(1, 0.15);
    mixer1.gain(2, 0.15);
    mixer1.gain(3, 0.15);
    mixer2.gain(1, 0.15);
    mixer2.gain(2, 0.15);
    delay(700);
  }

  const void playString1() { string1.noteOn(Cmajor[0], 1); }

  const void playString2() { string2.noteOn(Cmajor[1], 1); }

  const void playString3() { string3.noteOn(Cmajor[2], 1); }

  const void playString4() { string4.noteOn(Cmajor[3], 1); }

  const void playString5() { string5.noteOn(Cmajor[4], 1); }

  const void playString6() { string6.noteOn(Cmajor[5], 1); }

  // const void stopString1() {
  //     string1.noteOff();
  // }

  // const void stopString2() {
  //     string2.noteOff();
  // }

  // const void stopString3() {
  //     string3.noteOff();
  // }

  // const void stopString4() {
  //     string4.noteOff();
  // }

  // const void stopString5() {
  //     string5.noteOff();
  // }

  // const void stopString6() {
  //     string6.noteOff();
  // }

};  // class

}  // namespace _guitar
}  // namespace audio
}  // namespace kss