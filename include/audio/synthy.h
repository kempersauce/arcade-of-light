#pragma once

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

#include "audio/channel.h"    // for Channel
#include "audio/constants.h"  // for k*
#include "audio/sounds.h"     // for InitAudio
#include "serial/debug.h"     // for debug::*

namespace kss {
namespace audio {
namespace _synthy {
  AudioSynthWaveform       waveform1;      //xy=171,84 PAUL SHIT
  AudioSynthWaveform       waveform2;      //xy=178,148 PAUL SHIT
  AudioOutputI2S           audioOutput;    //xy=360,98 PAUL SHIT
  AudioOutputAnalogStereo  dacs1;          //xy=372,173
  AudioConnection          patchCord1(waveform1, 0, audioOutput, 0);
  AudioConnection          patchCord2(waveform1, 0, dacs1, 0);
  AudioConnection          patchCord3(waveform2, 0, audioOutput, 1);
  AudioConnection          patchCord4(waveform2, 0, dacs1, 1);
}// namespace synth
using namespace _synthy;

class Synthy {



public:

  float frequency = 256; //middle C 

  Synthy() {
    
    debug::println("hello");
  };

  const void InitSynth() {
    // Confirgure both to use "myWaveform" for WAVEFORM_ARBITRARY
    waveform1.arbitraryWaveform(WAVEFORM_SAMPLE_HOLD, 172.0);
    waveform2.arbitraryWaveform(WAVEFORM_SAWTOOTH, 172.0);

    // configure both waveforms for 440 Hz and maximum amplitude
    waveform1.frequency(440);
    waveform2.frequency(440);
    waveform1.amplitude(1.0);
    waveform2.amplitude(1.0);

    waveform1.begin(WAVEFORM_TRIANGLE);
  }

  const void Play() {
      AudioNoInterrupts();
      waveform1.frequency(frequency);
      waveform2.frequency(391.995);
      
      waveform1.amplitude(1.0);
      waveform2.amplitude(1.0);
      AudioInterrupts();

      AudioInterrupts();
      waveform1.begin(WAVEFORM_SAWTOOTH);
      waveform2.begin(WAVEFORM_SQUARE);
      AudioInterrupts();
      debug::println("played note");
  }

}; // class
} // namespace audio
} // namespace kss