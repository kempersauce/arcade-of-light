#pragma once

#include "display/constants.h"          // for k*
#include "display/instructo.h"          // for InstructoDisplay
#include "display/octo/octo_display.h"  // for OctoDisplay
#include "display/sub_display.h"        // for SubDisplay
#include "pins/pin_setup.h"             // for pins::*

namespace kss {
namespace display {

namespace _rocket {

constexpr size_t kNumStrips = kTowerStripCount + 1;  // +1 for instructo
constexpr size_t kLengthStrips = max(kTowerStripLength, kInstructoStripLength);

constexpr uint8_t kPinList[kNumStrips]{
    // clang-format off

    // Cable 1
    pins::Leds[0],
    pins::Leds[1],
    pins::Leds[2],
    pins::Leds[3],

    // Cable 2
    pins::Leds[4],

	// Cable 4 - instructo
	pins::Leds[12]

    // clang-format on
};

DMAMEM int kDisplayMemory[kNumStrips * kLengthStrips * 3 / 4];

}  // namespace _rocket

class RocketDisplay
    : public octo::OctoDisplay<_rocket::kNumStrips, _rocket::kLengthStrips> {
 public:
  SubDisplay main_display;
  InstructoDisplay instructo;

  RocketDisplay()
      : OctoDisplay(_rocket::kPinList, _rocket::kDisplayMemory),
        main_display{this, {0, 0}, {kTowerStripCount, kTowerStripLength}},
        instructo{&pixels[kTowerStripCount * _rocket::kLengthStrips]} {}
};

}  // namespace display
}  // namespace kss
