#pragma once

#include <FastLED.h>  // for CRGB

#include "display/display.h"  // for Display

/*
Display Class
holds the strips
*/

namespace kss {
namespace display {

template <size_t STRIP_COUNT, size_t STRIP_LENGTH>
class StandardDisplay : public Display {
  CRGB pixels[STRIP_COUNT][STRIP_LENGTH];

 public:
  StandardDisplay() : Display(STRIP_COUNT, STRIP_LENGTH) {}

  virtual inline CRGB& Pixel(size_t strip, size_t pixel) override {
#ifdef DEBUG
    CheckLocation(strip, pixel);
#endif
    return pixels[strip][pixel];
  }

 protected:
  // Inherited classes need this to initialize their own strip pinouts
  template <uint8_t PIN>
  void RegisterStrip(size_t index) {
    FastLED.addLeds<WS2812B, PIN, GRB>(pixels[index], lengthStrips);
  }
};

}  // namespace display
}  // namespace kss
