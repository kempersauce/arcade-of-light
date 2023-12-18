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
    // pins::Leds[5],
    // pins::Leds[6],
    // pins::Leds[7],

    // Cable 3
    // pins::Leds[8],

	// Cable 4 - instructo
	pins::LedInstructo[0]

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
      : OctoDisplay(_rocket::kPinList, _rocket::kDisplayMemory, GRID_SCALE_WIDE,
                    1),
        main_display{this, {0, 1}, {kTowerStripCount, kTowerStripLength - 1}},
        instructo{&pixels[kTowerStripCount * _rocket::kLengthStrips]} {
    // is_grb[1] = false;
    // is_grb[2] = false;
    // is_grb[3] = false;
  }
};

}  // namespace display
}  // namespace kss
