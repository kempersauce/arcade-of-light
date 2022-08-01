#pragma once

#include <Constants.h>

#include "display/octo_display.h"  // for OctoDisplay

namespace kss {
namespace display {

namespace {  // anonymous namespace - only used in this file

constexpr size_t kNumStrips = 20;
constexpr size_t kLengthStrips = 214;

constexpr uint8_t kPinList[kNumStrips]{
    LED_PIN_0,  LED_PIN_1,  LED_PIN_2,  LED_PIN_3,  LED_PIN_4,
    LED_PIN_5,  LED_PIN_6,  LED_PIN_7,  LED_PIN_8,  LED_PIN_9,
    LED_PIN_10, LED_PIN_11, LED_PIN_12, LED_PIN_13, LED_PIN_14,
    LED_PIN_15, LED_PIN_16, LED_PIN_17, LED_PIN_18, LED_PIN_19};

DMAMEM int kDisplayMemory[kNumStrips * kLengthStrips * 3 / 4];
}  // namespace

class TwentyDisplay : public OctoDisplay<kNumStrips, kLengthStrips> {
 public:
  TwentyDisplay() : OctoDisplay(kPinList, kDisplayMemory) {
    // RegisterStrip<LED_PIN_0>(0]);
    // RegisterStrip<LED_PIN_1>(1);
    // RegisterStrip<LED_PIN_2>(2);
    // RegisterStrip<LED_PIN_3>(3);
    // RegisterStrip<LED_PIN_4>(4);
    // RegisterStrip<LED_PIN_5>(5);
    // RegisterStrip<LED_PIN_6>(6);
    // RegisterStrip<LED_PIN_7>(7);
    // RegisterStrip<LED_PIN_8>(8);
    // RegisterStrip<LED_PIN_9>(9);
    // RegisterStrip<LED_PIN_10>(10);
    // RegisterStrip<LED_PIN_11>(11);
    // RegisterStrip<LED_PIN_12>(12);
    // RegisterStrip<LED_PIN_13>(13);
    // RegisterStrip<LED_PIN_14>(14);
    // RegisterStrip<LED_PIN_15>(15);
    // RegisterStrip<LED_PIN_16>(16);
    // RegisterStrip<LED_PIN_17>(17);
    // RegisterStrip<LED_PIN_18>(18);
    // RegisterStrip<LED_PIN_19>(19);
  }
};

}  // namespace display
}  // namespace kss
