#pragma once

#include "PinSetup.h"
#include "display/octo_display.h"  // for OctoDisplay

namespace kss {
namespace display {

namespace _twenty {

constexpr size_t kNumStrips = 20;
constexpr size_t kLengthStrips = 294;

constexpr uint8_t kPinList[kNumStrips]{
    // clang-format off

    // Cable 1
    pins::Leds[0],
    pins::Leds[1],
    pins::Leds[2],
    pins::Leds[3],

    // Cable 2
    pins::Leds[4],
    pins::Leds[5],
    pins::Leds[6],
    pins::Leds[7],

    // Cable 3
    pins::Leds[8],
    pins::Leds[9],
    pins::Leds[10],
    pins::Leds[11],

    // Cable 4
    pins::Leds[12],
    pins::Leds[13],
    pins::Leds[14],
    pins::Leds[15],

    // Cable 5
    pins::Leds[16],
    pins::Leds[17],
    pins::Leds[18],
    pins::Leds[19]

    // clang-format on
};

DMAMEM int kDisplayMemory[kNumStrips * kLengthStrips * 3 / 4];

}  // namespace _twenty
using namespace _twenty;

class TwentyDisplay : public OctoDisplay<kNumStrips, kLengthStrips> {
 public:
  TwentyDisplay() : OctoDisplay(kPinList, kDisplayMemory) {}
  virtual ~TwentyDisplay() = default;
};

}  // namespace display
}  // namespace kss
