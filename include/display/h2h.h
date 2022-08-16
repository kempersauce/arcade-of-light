#pragma once

#include <Constants.h>

#include "display/standard_display.h"  // for StandardDisplay

namespace kss {
namespace display {

class H2HDisplay : public StandardDisplay<8, 214> {
 public:
  H2HDisplay() : StandardDisplay() {
    RegisterStrip<LED_PIN_0>(0);
    RegisterStrip<LED_PIN_1>(1);
    RegisterStrip<LED_PIN_2>(2);
    RegisterStrip<LED_PIN_3>(3);
    RegisterStrip<LED_PIN_4>(4);
    RegisterStrip<LED_PIN_5>(5);
    RegisterStrip<LED_PIN_6>(6);
    RegisterStrip<LED_PIN_7>(7);
  }
};

}  // namespace display
}  // namespace kss
