#pragma once

#include "display/constants.h"          // for k*
#include "display/octo/octo_display.h"  // for OctoDisplay
#include "pins/pin_setup.h"             // for pins::*

namespace kss {
namespace display {

namespace _five {

constexpr size_t kNumStrips = kTowerStripCount;
constexpr size_t kLengthStrips = kTowerStripLength;

constexpr uint8_t kPinList[kNumStrips]{
    // clang-format off

    // Cable 1
    pins::Leds[0],
    pins::Leds[1],
    pins::Leds[2],
    pins::Leds[3],

    // Cable 2
    pins::Leds[4]

    // clang-format on
};

DMAMEM int kDisplayMemory[kNumStrips * kLengthStrips * 3 / 4];

}  // namespace _five

class FiveDisplay
    : public octo::OctoDisplay<_five::kNumStrips, _five::kLengthStrips> {
 public:
  FiveDisplay()
      : OctoDisplay(_five::kPinList, _five::kDisplayMemory, GRID_SCALE_WIDE) {}
};

}  // namespace display
}  // namespace kss
