#pragma once

#include <Constants.h>
#include <FastLED.h>     // for CRGB
#include <OctoWS2811.h>  // for octo-stuff

#include "display/display.h"          // for Display
#include "display/octo/controller.h"  // for octo stuff

/*
Display Class
holds the pixels
*/

namespace kss {
namespace display {

// const uint8_t kPinList[20]{LED_PIN_0,  LED_PIN_1,  LED_PIN_2,  LED_PIN_3,
//                            LED_PIN_4,  LED_PIN_5,  LED_PIN_6,  LED_PIN_7,
//                            LED_PIN_8,  LED_PIN_9,  LED_PIN_10, LED_PIN_11,
//                            LED_PIN_12, LED_PIN_13, LED_PIN_14, LED_PIN_15,
//                            LED_PIN_16, LED_PIN_17, LED_PIN_18, LED_PIN_19};

// constexpr size_t kNumStrips = 20;
// constexpr size_t kLengthStrips = 214;

template <size_t kNumStrips, size_t kLengthStrips>
class OctoDisplay : Display {
  // These buffers need to be large enough for all the pixels.
  // The total number of pixels is "ledsPerStrip * numPins".
  // Each pixel needs 3 bytes, so multiply by 3.  An "int" is
  // 4 bytes, so divide by 4.  The array is created using "int"
  // so the compiler will align it to 32 bit memory.
  // DMAMEM int displayMemory[kNumStrips * kLengthStrips * 3 / 4];
  int drawingMemory[kNumStrips * kLengthStrips * 3 / 4];

  CRGB pixels[kNumStrips * kLengthStrips];
  OctoWS2811 octo;
  CTeensy4Controller<RGB, WS2811_800kHz> controller;

 public:
  OctoDisplay(uint8_t* pin_list, int* displayMemory)
      : Display(kNumStrips, kLengthStrips),
        octo(kLengthStrips, displayMemory, drawingMemory,
             WS2811_RGB | WS2811_800kHz, strip_count, pin_list),
        controller(&octo) {
    octo.begin();

    FastLED.addLeds(&controller, pixels, strip_count * strip_length);
  }

  virtual inline CRGB& Pixel(size_t strip, size_t pixel) override {
#ifdef DEBUG
    CheckLocation(strip, pixel);
#endif
    return pixels[strip * strip_length + pixel];
  }
};

}  // namespace display
}  // namespace kss
