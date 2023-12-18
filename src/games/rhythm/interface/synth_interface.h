#pragma once

#include "controls/rhythm.h"                          // for RhythmController
#include "games/rhythm/interface/player_interface.h"  // for PlayerInterface

namespace kss {
namespace games {
namespace rhythm {

class SynthInterface : public PlayerInterface {
 public:
  SynthInterface(controls::RhythmController* controller, uint8_t serial_no)
      : PlayerInterface(controller, serial_no) {}

  void Update() override {
    for (uint8_t i = 0; i < controller->button_count; ++i) {
      if (controller->buttons[i]->IsDepressing()) {
        synth.StartInput(i);
      }
      if (controller->buttons[i]->IsReleasing()) {
        synth.StopInput(i);
      }
    }
  }
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
