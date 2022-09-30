#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

// Single color background
class ChargeBar : public Animation {
  const size_t height_min = 0;
  const CRGB color;

 public:
  const size_t height;
  const float blendFactor = 0.5;


  ChargeBar(CRGB color)
      : Animation(),
        color{color} {}

  void draw(display::Display* display) {
    //TODO: we could use dithering here 
    totalHeight = unitsFilled * unitHeight;
    for (size_t y = 0; y < height; ++y) {
      display->BlendPixel(0, y, color, blendFactor);
      display->BlendPixel(display->size.x - 1, y, color, blendFacor);
    }
  }
};

}  // namespace animation
}  // namespace kss