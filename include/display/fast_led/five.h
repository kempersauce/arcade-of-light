#pragma once

#include "display/fast_led/fast_led_display.h"  // for FastLedDisplay
#include "pins/pin_setup.h"                     // for pins::*

namespace kss {
namespace display {
namespace fast_led {

class FiveDisplay : public FastLedDisplay<5, 300> {
 public:
  FiveDisplay() : FastLedDisplay() {
    RegisterStrip<pins::Leds[0]>(0);
    RegisterStrip<pins::Leds[1]>(1);
    RegisterStrip<pins::Leds[2]>(2);
    RegisterStrip<pins::Leds[3]>(3);
    RegisterStrip<pins::Leds[4]>(4);
  }
};

}  // namespace fast_led
}  // namespace display
}  // namespace kss
