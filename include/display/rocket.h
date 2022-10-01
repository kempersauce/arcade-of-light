#pragma once

#include "display/octo_display.h"  // for OctoDisplay
#include "pins/pin_setup.h"        // for pins::*

namespace kss {
namespace display {

namespace _rocket {

constexpr size_t kNumStrips = 5;
constexpr size_t kLengthStrips = 294;

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

}  // namespace _rocket

class RocketDisplay
    : public OctoDisplay<_rocket::kNumStrips, _rocket::kLengthStrips> {
 public:
  RocketDisplay() : OctoDisplay(_rocket::kPinList, _rocket::kDisplayMemory) {}
};

}  // namespace display
}  // namespace kss
