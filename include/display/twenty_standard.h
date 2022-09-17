#pragma once

#include <Constants.h>

#include "display/standard_display.h"  // for StandardDisplay

namespace kss {
namespace display {

namespace twenty_standard {

constexpr size_t kNumStrips = 20;
constexpr size_t kLengthStrips = 300;

}  // namespace twenty_standard

class TwentyDisplayStandard
    : public StandardDisplay<twenty_standard::kNumStrips,
                             twenty_standard::kLengthStrips> {
 public:
  TwentyDisplayStandard() : StandardDisplay() {
    RegisterStrip<pins::Leds[0]>(0);
    RegisterStrip<pins::Leds[1]>(1);
    RegisterStrip<pins::Leds[2]>(2);
    RegisterStrip<pins::Leds[3]>(3);
    RegisterStrip<pins::Leds[4]>(4);
    RegisterStrip<pins::Leds[5]>(5);
    RegisterStrip<pins::Leds[6]>(6);
    RegisterStrip<pins::Leds[7]>(7);
    RegisterStrip<pins::Leds[8]>(8);
    RegisterStrip<pins::Leds[9]>(9);
    RegisterStrip<pins::Leds[10]>(10);
    RegisterStrip<pins::Leds[11]>(11);
    RegisterStrip<pins::Leds[12]>(12);
    RegisterStrip<pins::Leds[13]>(13);
    RegisterStrip<pins::Leds[14]>(14);
    RegisterStrip<pins::Leds[15]>(15);
    RegisterStrip<pins::Leds[16]>(16);
    RegisterStrip<pins::Leds[17]>(17);
    RegisterStrip<pins::Leds[18]>(18);
    RegisterStrip<pins::Leds[19]>(19);
  }
  virtual ~TwentyDisplayStandard() = default;
};

}  // namespace display
}  // namespace kss
