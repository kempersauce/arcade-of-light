#pragma once

#include "display/standard_display.h"  // for StandardDisplay
#include "pins/pin_setup.h"            // for pins::*

namespace kss {
namespace display {

class FiveDisplay : public StandardDisplay<5, 300> {
 public:
  FiveDisplay() : StandardDisplay() {
    RegisterStrip<pins::Leds[0]>(0);
    RegisterStrip<pins::Leds[1]>(1);
    RegisterStrip<pins::Leds[2]>(2);
    RegisterStrip<pins::Leds[3]>(3);
    RegisterStrip<pins::Leds[4]>(4);
  }
};

}  // namespace display
}  // namespace kss
