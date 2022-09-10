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
    RegisterStrip<LED_PIN_0>(0);
    RegisterStrip<LED_PIN_1>(1);
    RegisterStrip<LED_PIN_2>(2);
    RegisterStrip<LED_PIN_3>(3);
    RegisterStrip<LED_PIN_4>(4);
    RegisterStrip<LED_PIN_5>(5);
    RegisterStrip<LED_PIN_6>(6);
    RegisterStrip<LED_PIN_7>(7);
    RegisterStrip<LED_PIN_8>(8);
    RegisterStrip<LED_PIN_9>(9);
    RegisterStrip<LED_PIN_10>(10);
    RegisterStrip<LED_PIN_11>(11);
    RegisterStrip<LED_PIN_12>(12);
    RegisterStrip<LED_PIN_13>(13);
    RegisterStrip<LED_PIN_14>(14);
    RegisterStrip<LED_PIN_15>(15);
    RegisterStrip<LED_PIN_16>(16);
    RegisterStrip<LED_PIN_17>(17);
    RegisterStrip<LED_PIN_18>(18);
    RegisterStrip<LED_PIN_19>(19);
  }
  virtual ~TwentyDisplayStandard() = default;
};

}  // namespace display
}  // namespace kss
