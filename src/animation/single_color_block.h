#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

// Single color background
class SingleColorBlock : public Animation {
  const size_t height_min;
  const size_t height_max;

  const CRGB color;

 public:
  SingleColorBlock(size_t height_min, size_t height_max, CRGB color)
      : Animation(),
        height_min{height_min},
        height_max{height_max},
        color{color} {}

  void Draw(display::Display* display) {
    for (size_t x = 0; x < display->size.x; ++x) {
      for (size_t y = height_min; y < height_max; ++y) {
        display->Pixel(x, y) = color;
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
