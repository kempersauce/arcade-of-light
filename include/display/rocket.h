#pragma once

#include <Constants.h>

#include "PinSetup.h"                  // for pins::*
#include "display/standard_display.h"  // for StandardDisplay

namespace kss {
namespace display {

class RocketDisplay : public StandardDisplay<3, 300> {
 public:
  RocketDisplay() : StandardDisplay() {
    RegisterStrip<pins::Leds[0]>(0);
    RegisterStrip<pins::Leds[1]>(1);
    RegisterStrip<pins::Leds[2]>(2);
  }
};

}  // namespace display
}  // namespace kss
