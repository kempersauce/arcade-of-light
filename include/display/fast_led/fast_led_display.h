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
class FastLedDisplay : public Display {
 protected:
  CRGB pixels[STRIP_COUNT][STRIP_LENGTH] = {};

 public:
  FastLedDisplay(math::Vector2D<float> grid_scale)
      : Display({STRIP_COUNT, STRIP_LENGTH}, grid_scale) {}

  virtual ~FastLedDisplay() = default;

  // Delete copy constructor & assignment operator, force them to make their own
  FastLedDisplay(const FastLedDisplay*) = delete;
  FastLedDisplay* operator=(const FastLedDisplay*) = delete;
  FastLedDisplay(FastLedDisplay*&) = delete;
  FastLedDisplay* operator=(FastLedDisplay*&) = delete;

  virtual inline CRGB& Pixel(size_t strip, size_t pixel) override {
    if (!CheckLocation(strip, pixel)) {
      return dummy_pixel;
    }
    return pixels[strip][pixel];
  }

  virtual void Show() override { FastLED.show(); }

 protected:
  // Inherited classes need this to initialize their own strip pinouts
  template <uint8_t PIN, EOrder PIX_CONF = GRB>
  const void RegisterStrip(const size_t index, const size_t length = 0) {
    // Guard against registering extra strips on accident
    if (index < size.x) {
      FastLED.addLeds<WS2812B, PIN, PIX_CONF>(pixels[index],
                                              length == 0 ? size.y : length);
    }
  }
};

}  // namespace fast_led
}  // namespace display
}  // namespace kss
