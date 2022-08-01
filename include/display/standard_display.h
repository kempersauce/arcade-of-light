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

  virtual inline CRGB& Pixel(size_t strip_index, size_t pixel_index) override {
    return pixels[strip_index][pixel_index];
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
