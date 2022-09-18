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
  StandardDisplay() : Display({STRIP_COUNT, STRIP_LENGTH}) {}
  virtual ~StandardDisplay() = default;

  // Delete copy constructor & assignment operator, force them to make their own
  StandardDisplay(const StandardDisplay*) = delete;
  StandardDisplay* operator=(const StandardDisplay*) = delete;
  StandardDisplay(StandardDisplay*&) = delete;
  StandardDisplay* operator=(StandardDisplay*&) = delete;

  virtual inline CRGB& Pixel(size_t strip, size_t pixel) override {
    CheckLocation(strip, pixel);
    return pixels[strip][pixel];
  }

  virtual void Show() override { FastLED.show(); }

 protected:
  // Inherited classes need this to initialize their own strip pinouts
  template <uint8_t PIN>
  const void RegisterStrip(const size_t index) {
    // Guard against registering extra strips on accident
    if (index < size.x) {
      FastLED.addLeds<WS2812B, PIN, GRB>(pixels[index], size.y);
    }
  }
};

}  // namespace display
}  // namespace kss
