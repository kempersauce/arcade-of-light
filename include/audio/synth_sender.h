#pragma once

#include <HardwareSerial.h>  // for HardwareSerial

#include "audio/synth_sender_raw.h"  // for SynthSenderRaw
#include "controls/button.h"         // for Button
#include "serial/debug.h"            // for Debug

namespace kss {
namespace audio {

class SynthSender : SynthSenderRaw {
  // Button time
  controls::Button* btns[6];

 public:
  // Constructor: starts serial connection to audioSlave
  SynthSender(controls::Button* up, controls::Button* down,
              controls::Button* left, controls::Button* right,
              controls::Button* a, controls::Button* b,
              HardwareSerial* serial = &Serial1)
      : SynthSenderRaw{serial}, btns{up, down, left, right, a, b} {}

  // checks if any buttons have changed state
  void checkButtonChange() {
    for (size_t i = 0; i < 6; ++i) {
      if (btns[i]->IsDepressing()) {
        StartInput(i);
      }
      if (btns[i]->IsReleasing()) {
        StopInput(i);
      }
    }
  }
};

}  // namespace audio
}  // namespace kss
