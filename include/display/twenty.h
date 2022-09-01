#pragma once

#include <Constants.h>

#include "display/octo_display.h"  // for OctoDisplay

namespace kss {
namespace display {

namespace _twenty {

constexpr size_t kNumStrips = 20;
constexpr size_t kLengthStrips = 200;

constexpr uint8_t kPinList[kNumStrips]{
    LED_PIN_0,
    LED_PIN_1,
    LED_PIN_2,
    LED_PIN_3
    ,
    LED_PIN_4,
    LED_PIN_5,
    LED_PIN_6,
    LED_PIN_7
    ,
    LED_PIN_8,
    LED_PIN_9,
    LED_PIN_10,
    LED_PIN_11
    ,
    LED_PIN_12,
    LED_PIN_13,
    LED_PIN_14,
    LED_PIN_15
    ,
    LED_PIN_16,
    LED_PIN_17,
    LED_PIN_18,
    LED_PIN_19
};

DMAMEM int kDisplayMemory[kNumStrips * kLengthStrips * 3 / 4];

}  // namespace _twenty
using namespace _twenty;

class TwentyDisplay
    : public OctoDisplay<kNumStrips, kLengthStrips> {
 public:
  TwentyDisplay() : OctoDisplay(kPinList, kDisplayMemory) {}

};

}  // namespace display
}  // namespace kss
