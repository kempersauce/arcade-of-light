#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

class WavePulse : public Animation {
  const size_t height;
  const CRGB color;

 public:
  size_t y;

  WavePulse(size_t height, CRGB color)
      : Animation(), height{height}, color{color} {}

  void Move() override {}

  void Draw(display::Display* display) {
    for (size_t i = 0; i < height; ++i) {
      const float presence = (float)(height - i) / (float)height;
      for (size_t x = 0; x < display->size.width; ++x) {
        const size_t y_adjusted = (y + i) % display->size.height;
        display->BlendPixel(x, y_adjusted, color, presence);
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
