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
  OctoDisplay(const uint8_t* pin_list, int* displayMemory)
      : Display(kNumStrips, kLengthStrips),
        octo(kLengthStrips, displayMemory, drawingMemory,
             WS2811_RGB | WS2811_800kHz, kNumStrips, pin_list),
        controller(&octo) {
    octo.begin();

    FastLED.addLeds(&controller, pixels, kNumStrips * kLengthStrips);
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
