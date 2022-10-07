#pragma once

#include "display/constants.h"          // for k*
#include "display/instructo.h"          // for InstructoDisplay
#include "display/octo/octo_display.h"  // for OctoDisplay
#include "display/sub_display.h"        // for SubDisplay
#include "pins/pin_setup.h"             // for pins::*

namespace kss {
namespace display {

namespace _h2h {

constexpr size_t kNumStrips = kTableStripCount + 2;  // +2 for instructos
constexpr size_t kLengthStrips = max(kTableStripLength, kInstructoStripLength);

constexpr uint8_t kPinList[kNumStrips]{
    // clang-format off

    // Cable 1
    pins::Leds[0],
    pins::Leds[1],
    pins::Leds[2],
    pins::Leds[3],

    // Cable 2
    // pins::Leds[4],
    // pins::Leds[5],
    // pins::Leds[6],
    // pins::Leds[7]

    // Cable 3
    pins::Leds[8],
    pins::Leds[9],
    pins::Leds[10],
    pins::Leds[11],

    // Cable 4 - instructo A
	pins::LedInstructo[0],

    // Cable 5 - instructo B
	pins::LedInstructo[1]

    // clang-format on
};

DMAMEM int kDisplayMemory[kNumStrips * kLengthStrips * 3 / 4];

}  // namespace _h2h

class H2HDisplay
    : public octo::OctoDisplay<_h2h::kNumStrips, _h2h::kLengthStrips> {
 public:
  SubDisplay main_display;
  InstructoDisplay instructo_a;
  InstructoDisplay instructo_b;

  H2HDisplay()
      : OctoDisplay(_h2h::kPinList, _h2h::kDisplayMemory, 2),
        main_display{this, {0, 0}, {kTableStripCount, kTableStripLength}},
        instructo_a{&pixels[(kTableStripCount + 0) * _h2h::kLengthStrips]},
        instructo_b{&pixels[(kTableStripCount + 1) * _h2h::kLengthStrips]} {}
};

}  // namespace display
}  // namespace kss
