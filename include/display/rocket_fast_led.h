#pragma once

#include "display/constants.h"                  // for k*
#include "display/fast_led/fast_led_display.h"  // for FastLedDisplay
#include "display/instructo.h"                  // for InstructoDisplay
#include "display/sub_display.h"                // for SubDisplay
#include "pins/pin_setup.h"                     // for pins::*

namespace kss {
namespace display {

namespace _rocket_fast_led {

constexpr size_t kNumStrips = kTowerStripCount + 1;  // +1 for instructo
constexpr size_t kLengthStrips = max(kTowerStripLength, kInstructoStripLength);

}  // namespace _rocket_fast_led

class RocketDisplay
    : public fast_led::FastLedDisplay<_rocket_fast_led::kNumStrips,
                                      _rocket_fast_led::kLengthStrips> {
 public:
  SubDisplay main_display;
  InstructoDisplay instructo;

  RocketDisplay() : FastLedDisplay(GRID_SCALE_WIDE),
        main_display{this, {0, 1}, {kTowerStripCount, kTowerStripLength - 1}},
		instructo{pixels[kTowerStripCount]} {
    // Cable 1
    RegisterStrip<pins::Leds[0], RGB>(0, kTowerStripLength);
    RegisterStrip<pins::Leds[1]>(1, kTowerStripLength);
    RegisterStrip<pins::Leds[2]>(2, kTowerStripLength);
    RegisterStrip<pins::Leds[3]>(3, kTowerStripLength);

    // Cable 2
    RegisterStrip<pins::Leds[4], RGB>(4, kTowerStripLength);

    // Instructo
    RegisterStrip<pins::LedInstructo[0]>(5, kInstructoStripLength);
  }
};

}  // namespace display
}  // namespace kss
