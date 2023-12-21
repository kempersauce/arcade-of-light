#pragma once

#include "display/constants.h"          // for k*
#include "display/instructo.h"          // for InstructoDisplay
#include "display/octo/octo_display.h"  // for OctoDisplay
#include "display/sub_display.h"        // for SubDisplay
#include "pins/pin_setup.h"             // for pins::*

namespace kss {
namespace display {

namespace _h2h_5_test {

constexpr size_t kNumStrips = kTowerStripCount + 1;  // +1 for instructo
constexpr size_t kLengthStrips = max(kTableStripLength, kInstructoStripLength);

constexpr uint8_t kPinList[kNumStrips]{
    // clang-format off

    // Cable 1
    pins::Leds[0],
    pins::Leds[1],
    pins::Leds[2],
    pins::Leds[3],

    // Cable 2
    pins::Leds[8],

	// Cable 4 - instructo
	pins::Leds[12]

    // clang-format on
};

DMAMEM int kDisplayMemory[kNumStrips * kLengthStrips * 3 / 4];

}  // namespace _h2h_5_test

class H2H5TestDisplay : public octo::OctoDisplay<_h2h_5_test::kNumStrips,
                                                 _h2h_5_test::kLengthStrips> {
 public:
  SubDisplay main_display;
  InstructoDisplay instructo;

  H2H5TestDisplay()
      : OctoDisplay(_h2h_5_test::kPinList, _h2h_5_test::kDisplayMemory,
                    GRID_SCALE_WIDE),
        main_display{this, {0, 0}, {kTowerStripCount, kTableStripLength}},
        instructo{&pixels[kTowerStripCount * _h2h_5_test::kLengthStrips]} {}
};

}  // namespace display
}  // namespace kss
