#pragma once

#include <Constants.h>

#include "display/standard_display.h"  // for StandardDisplay

namespace kss {
namespace display {

class H2HDisplay : public StandardDisplay<8, 214> {
 public:
  H2HDisplay() : StandardDisplay() {
    RegisterStrip<pins::Leds[0]>(0);
    RegisterStrip<pins::Leds[1]>(1);
    RegisterStrip<pins::Leds[2]>(2);
    RegisterStrip<pins::Leds[3]>(3);
    RegisterStrip<pins::Leds[4]>(4);
    RegisterStrip<pins::Leds[5]>(5);
    RegisterStrip<pins::Leds[6]>(6);
    RegisterStrip<pins::Leds[7]>(7);
  }
};

}  // namespace display
}  // namespace kss
