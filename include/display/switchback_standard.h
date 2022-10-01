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
class SwitchbackStandardDisplay : public Display {
  CRGB pixels[STRIP_COUNT * STRIP_LENGTH];

 public:
  SwitchbackStandardDisplay() : Display({STRIP_COUNT, STRIP_LENGTH}) {}
  virtual ~SwitchbackStandardDisplay() = default;

  // Delete copy constructor & assignment operator, force them to make their own
  SwitchbackStandardDisplay(const SwitchbackStandardDisplay*) = delete;
  SwitchbackStandardDisplay* operator=(const SwitchbackStandardDisplay*) =
      delete;
  SwitchbackStandardDisplay(SwitchbackStandardDisplay*&) = delete;
  SwitchbackStandardDisplay* operator=(SwitchbackStandardDisplay*&) = delete;

  virtual inline CRGB& Pixel(size_t x, size_t y) override {
    if (!CheckLocation(x, y)) {
      return dummy_pixel;
    }

    if (y % 2 == 1) {
      x = size.x - x - 1;
    }

    return pixels[y * size.x + x];
  }

  virtual void Show() override { FastLED.show(); }

 protected:
  // Inherited classes need this to initialize their own strip pinouts
  template <uint8_t PIN>
  const void RegisterStrip() {
    // Guard against registering extra strips on accident
    FastLED.addLeds<WS2812B, PIN, GRB>(pixels, STRIP_COUNT * STRIP_LENGTH);
  }
};

}  // namespace display
}  // namespace kss
