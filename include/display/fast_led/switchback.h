#pragma once

#include <FastLED.h>  // for FastLED

#include "display/display.h"  // for Display

/*
Display Class
holds the strips
*/

namespace kss {
namespace display {
namespace fast_led {

template <size_t STRIP_COUNT, size_t STRIP_LENGTH>
class SwitchbackDisplay : public Display {
  CRGB pixels[STRIP_COUNT * STRIP_LENGTH];

 public:
  SwitchbackDisplay() : Display({STRIP_COUNT, STRIP_LENGTH}, GRID_SCALE_1_1) {}
  virtual ~SwitchbackDisplay() = default;

  // Delete copy constructor & assignment operator, force them to make their own
  SwitchbackDisplay(const SwitchbackDisplay*) = delete;
  SwitchbackDisplay* operator=(const SwitchbackDisplay*) = delete;
  SwitchbackDisplay(SwitchbackDisplay*&) = delete;
  SwitchbackDisplay* operator=(SwitchbackDisplay*&) = delete;

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
  void RegisterStrip() {
    // Guard against registering extra strips on accident
    FastLED.addLeds<WS2812B, PIN, GRB>(pixels, STRIP_COUNT * STRIP_LENGTH);
  }
};

}  // namespace fast_led
}  // namespace display
}  // namespace kss
