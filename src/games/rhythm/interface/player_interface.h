#pragma once

#include "audio/synth_sender_raw.h"  // for SynthSenderRaw
#include "controls/button.h"         // for Button
#include "controls/rhythm.h"         // for RhythmController
#include "serial/hw_serials.h"       // for kHwSerials

namespace kss {
namespace games {
namespace rhythm {

class PlayerInterface {
 protected:
  controls::RhythmController* const controller;
  audio::SynthSenderRaw synth;

 public:
  PlayerInterface(controls::RhythmController* controller, uint8_t serial_no)
      : controller{controller}, synth{serial::kHwSerials[serial_no]} {}
  virtual ~PlayerInterface() = default;

  virtual void Start() {}
  virtual void Update() = 0;
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
