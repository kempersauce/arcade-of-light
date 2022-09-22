#pragma once

#include "display/octo_display.h"  // for OctoDisplay
#include "pins/pin_setup.h"        // for pins::*

namespace kss {
namespace display {

namespace _single_octo {

constexpr size_t kNumStrips = 1;
constexpr size_t kLengthStrips = 214;

constexpr uint8_t kPinList[kNumStrips]{
    // clang-format off

    // Cable 1
    pins::Leds[5]

    // clang-format on
};

DMAMEM int kDisplayMemory[kNumStrips * kLengthStrips * 3 / 4];

}  // namespace _single_octo
using namespace _single_octo;

class SingleDisplay : public OctoDisplay<kNumStrips, kLengthStrips> {
 public:
  SingleDisplay() : OctoDisplay(kPinList, kDisplayMemory) {}
};

}  // namespace display
}  // namespace kss
