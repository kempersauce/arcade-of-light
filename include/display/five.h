#pragma once

#include <Constants.h>

#include "display/standard_display.h"  // for StandardDisplay

namespace kss {
namespace display {

class FiveDisplay : public StandardDisplay<5, 300> {
 public:
  FiveDisplay() : StandardDisplay() {
    RegisterStrip<LED_PIN_0>(0);
    RegisterStrip<LED_PIN_1>(1);
    RegisterStrip<LED_PIN_2>(2);
    RegisterStrip<LED_PIN_3>(3);
    RegisterStrip<LED_PIN_4>(4);
  }
};

}  // namespace display
}  // namespace kss
