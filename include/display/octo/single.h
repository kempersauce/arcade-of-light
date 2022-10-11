#pragma once

#include "display/octo/octo_display.h"  // for OctoDisplay
#include "pins/pin_setup.h"             // for pins::*

namespace kss {
namespace display {
namespace octo {

namespace _single {

constexpr size_t kNumStrips = 1;
constexpr size_t kLengthStrips = 300;

constexpr uint8_t kPinList[kNumStrips]{
    // clang-format off

    // Cable 1
    pins::Leds[0]

    // clang-format on
};

DMAMEM int kDisplayMemory[kNumStrips * kLengthStrips * 3 / 4];

}  // namespace _single

class SingleDisplay
    : public OctoDisplay<_single::kNumStrips, _single::kLengthStrips> {
 public:
  SingleDisplay()
      : OctoDisplay(_single::kPinList, _single::kDisplayMemory,
                    GRID_SCALE_WIDE) {}
};

}  // namespace octo
}  // namespace display
}  // namespace kss
