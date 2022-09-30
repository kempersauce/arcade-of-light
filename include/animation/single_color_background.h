#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

// Single color background
class SingleColorBG : public Animation {
  const CRGB color;

 public:
  SingleColorBG(CRGB color = CRGB::Black) : Animation(), color{color} {}

  void Draw(display::Display* display) {
    for (size_t x = 0; x < display->size.x; ++x) {
      for (size_t y = 0; y < display->size.y; ++y) {
        display->Pixel(x, y) = color;
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
