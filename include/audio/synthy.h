#pragma once

#include <Audio.h>
#include <Bounce.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

// #include "audio/channel.h"    // for Channel
#include "audio/constants.h"  // for k*
// #include "audio/sounds.h"     // for InitAudio
#include "serial/debug.h"  // for debug::*

namespace kss {
namespace audio {
namespace _synthy {
AudioSynthWaveform waveform1;   // xy=171,84 PAUL SHIT
AudioSynthWaveform waveform2;   // xy=178,148 PAUL SHIT
AudioOutputI2S i2s1;            // xy=360,98 PAUL SHIT
AudioOutputAnalogStereo dacs1;  // xy=372,173
AudioConnection patchCord1(waveform1, 0, i2s1, 0);
AudioConnection patchCord2(waveform1, 0, dacs1, 0);
AudioConnection patchCord3(waveform2, 0, i2s1, 1);
AudioConnection patchCord4(waveform2, 0, dacs1, 1);
AudioControlSGTL5000 sgtl5000_1;  // xy=239,232
}  // namespace synth
using namespace _synthy;

class Synthy {
 public:
  float frequency = 256;  // middle C
  float sequence[3] = {256, 329.63, 391.995};
  uint32_t next_hit = 0;
  size_t i = 0;

  Synthy() {
    debug::println("hello");
  };

  const void InitSynth() {
    Serial.begin(9600);

    // Audio connections require memory to work.  For more
    // detailed information, see the MemoryAndCpuUsage example
    AudioMemory(10);
    // Confirgure both to use "myWaveform" for WAVEFORM_ARBITRARY
    // waveform1.arbitraryWaveform(WAVEFORM_SAMPLE_HOLD, 172.0);
    // waveform2.arbitraryWaveform(WAVEFORM_SAWTOOTH, 172.0);

    // Comment these out if not using the audio adaptor board.
    // This may wait forever if the SDA & SCL pins lack
    // pullup resistors
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.8);  // caution: very loud - use oscilloscope only!

    // configure both waveforms for 440 Hz and maximum amplitude
    waveform1.frequency(440);
    waveform2.frequency(440);
    waveform1.amplitude(1.0);
    waveform2.amplitude(1.0);

    waveform1.begin(WAVEFORM_TRIANGLE);
  }

  const void Play() {
    AudioNoInterrupts();
    const uint32_t now = millis();
    if (now >= next_hit) {
      // do it
      if (++i >= 3) {
        i = 0;
      }
    }
    next_hit = now + 500;
  

  waveform1.frequency(sequence[i]);
  waveform2.frequency(391.995);

  // waveform1.amplitude(1.0);
  // waveform2.amplitude(1.0);
  AudioInterrupts();

  AudioNoInterrupts();
  waveform1.begin(0);
  waveform2.begin(WAVEFORM_SINE);
  AudioInterrupts();
  debug::println("played note");
}

};  // class
}  // namespace audio
}  // namespace kss