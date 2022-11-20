#pragma once

#include <Audio.h>

#include <vector>

#include "audio/channel.h"    // for Channel
#include "audio/constants.h"  // for k*
#include "serial/debug.h"     // for Debug

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav6;  //xy=144,449
AudioPlaySdWav           playSdWav3; //xy=146,290
AudioPlaySdWav           playSdWav5; //xy=147,394
AudioPlaySdWav           playSdWav1;     //xy=148,201
AudioPlaySdWav           playSdWav2; //xy=148,246
AudioPlaySdWav           playSdWav7; //xy=149,507
AudioPlaySdWav           playSdWav4; //xy=150,341
AudioPlaySdWav           playSdWav8; //xy=153,576
AudioMixer4              mixer2;         //xy=395,462
AudioMixer4              mixer1;         //xy=401,200
AudioMixer4              mixer3; //xy=565,329
AudioOutputI2S           i2s1;           //xy=737,329
AudioConnection          patchCord1(playSdWav6, 0, mixer2, 1);
AudioConnection          patchCord2(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord3(playSdWav5, 0, mixer2, 0);
AudioConnection          patchCord4(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord5(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord6(playSdWav7, 0, mixer2, 2);
AudioConnection          patchCord7(playSdWav4, 0, mixer1, 3);
AudioConnection          patchCord8(playSdWav8, 0, mixer2, 3);
AudioConnection          patchCord9(mixer2, 0, mixer3, 1);
AudioConnection          patchCord10(mixer1, 0, mixer3, 0);
AudioConnection          patchCord11(mixer3, 0, i2s1, 0);
AudioConnection          patchCord12(mixer3, 0, i2s1, 1);
// GUItool: end automatically generated code


namespace kss {
namespace audio {

class WavAudioManagerLife {
 public:
  WavAudioManager() {}

  void Setup() {

    mixer1.gain(0,0.5);
    mixer1.gain(1,0.5);
    mixer1.gain(2,0.5);
    mixer1.gain(3,0.5);

    mixer2.gain(0,0.5);
    mixer2.gain(1,0.5);
    mixer2.gain(2,0.5);
    mixer2.gain(3,0.5);
    
    
    //mixer1
    playSdWav1.play("BEE.WAV");
    playSdWav2.play("FROGGY.WAV");
    playSdWav3.play("OWL.WAV");
    playSdWav4.play("NATPAD.WAV");

    playSdWav5.play("STREAM.WAV");
    playSdWav6.play("THUNDER.WAV");
    playSdWav7.play("KILLDEER.WAV");
    playSdWav8.play("KATYDID.WAV");
  }

  void AdjustGain(const size_t index, const float level) {
    if(index <=3) {
      mixer1.gain(index, level);
    } else {
      mixer2.gain(index - 4, level);
    }
  }
};

}  // namespace audio
}  // namespace kss
