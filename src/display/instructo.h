#pragma once

#include <pixeltypes.h>  // for CRGB

#include "display/constants.h"  // for k*
#include "display/display.h"    // for Display
#include "serial/debug.h"       // for Debug

namespace kss {
namespace display {

class InstructoDisplay : public Display {
  CRGB* pixels;

 public:
  InstructoDisplay(CRGB* pixels)
      : Display({kInstructoRowCount, kInstructoColumnCount}, GRID_SCALE_1_1), pixels{pixels} {}

 public:
  inline CRGB& Pixel(size_t x, size_t y) override {
    if (!CheckLocation(x, y)) {
      return dummy_pixel;
    }

    if (y % 2 == 1) {
      x = size.x - x - 1;
    }

    return pixels[y * size.x + x];
  }

  void Show() override {
    // Leave this blank - let the parent handle showing
  }
};

}  // namespace display
}  // namespace kss
