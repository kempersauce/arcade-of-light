#pragma once

#include "display/standard_display.h"  // for StandardDisplay
#include "pins/pin_setup.h"            // for pins::*

namespace kss {
namespace display {

class SingleDisplay : public StandardDisplay<1, 214> {
 public:
  SingleDisplay() : StandardDisplay() {
    RegisterStrip<pins::Leds[5]>(0);
  }
};

}  // namespace display
}  // namespace kss
