#pragma once

#include <Audio.h>

#include "serial/debug.h"  // for Debug

namespace kss {
namespace audio {
namespace drumWav {

// SETUP CONNECTIONS HERE
AudioPlaySdWav drum1;
AudioPlaySdWav drum2;
AudioPlaySdWav drum3;
AudioPlaySdWav drum4;
AudioPlaySdWav drum5;
AudioPlaySdWav drum6;

AudioMixer4 mixer1;
AudioMixer4 mixer2;
AudioMixer4 mixerMain;

AudioOutputI2S i2s1;  // xy=360,98 PAUL SHIT

AudioConnection patchCord1(drum1, 0, mixer1, 0);
AudioConnection patchCord2(drum2, 0, mixer1, 1);
AudioConnection patchCord3(drum3, 0, mixer1, 2);
AudioConnection patchCord4(drum4, 0, mixer1, 3);
AudioConnection patchCord5(drum5, 0, mixer2, 0);
AudioConnection patchCord6(drum6, 0, mixer2, 1);

AudioConnection patchCordMain1(mixer1, 0, mixerMain, 0);
AudioConnection patchCordMain2(mixer2, 0, mixerMain, 1);

// final output
AudioConnection patchCordOut1(mixerMain, 0, i2s1, 0);
AudioConnection patchCordOut2(mixerMain, 0, i2s1, 1);

class DrumWav {
 public:
  DrumWav() { Debug("Pa rum pa pa pum"); }

  const void playDrum1() { drum1.play("808CLAP.WAV"); }
  const void playDrum2() { drum2.play("808CRSH1.WAV"); }

  const void stopDrum2() { drum2.stop(); }
  const void playDrum3() { drum3.play("808TOMH.WAV"); }
  const void playDrum4() { drum4.play("808HHCL.WAV"); }
  const void playDrum5() { drum5.play("808BD01.WAV"); }
  const void playDrum6() { drum6.play("808SNR.WAV"); }

};  // class DrumWav

}  // namespace drumWav
}  // namespace audio
}  // namespace kss
