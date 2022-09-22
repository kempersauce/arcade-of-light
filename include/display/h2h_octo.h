#pragma once

#include "display/octo_display.h"  // for OctoDisplay
#include "pins/pin_setup.h"        // for pins::*

namespace kss {
namespace display {

namespace _h2h_octo {

constexpr size_t kNumStrips = 8;
constexpr size_t kLengthStrips = 214;

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
    pins::Leds[11]

    // clang-format on
};

DMAMEM int kDisplayMemory[kNumStrips * kLengthStrips * 3 / 4];

}  // namespace _h2h_octo
using namespace _h2h_octo;

class H2HDisplay : public OctoDisplay<kNumStrips, kLengthStrips> {
 public:
  H2HDisplay() : OctoDisplay(kPinList, kDisplayMemory) {}
};

}  // namespace display
}  // namespace kss
