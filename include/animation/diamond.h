#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

// Single color background
class Diamond : public Animation {
  const size_t height;
  const size_t width;

  const CRGB color1;
  const CRGB color2;
  const CRGB color3;
  const size_t center_x;
  const size_t center_y;
  const size_t slope = 2;


 public:
  Diamond(int center_x, int center_y, int height, int width, CRGB color1)
      : Animation(),
        center_x{center_x},
        center_y{center_y},
        height{height},
        width{width},
        color1{color1} {}

  void Draw(display::Display* display) {
    for (size_t x = 0; x <= (width)/2 + 1; ++x) {
        size_t x_cord = x;
        size_t y_cord = center_y + x * slope;
        size_t y_cord_inv = center_y - x * slope;
        size_t x_cord_inv = center_x - x + width/2 - 1;
        // top left quad
        display->Pixel(x_cord,y_cord) = color1;
        display->Pixel(x_cord,y_cord + 1) = color1;
        // top right quad
        display->Pixel(x_cord_inv,y_cord) = color1;
        display->Pixel(x_cord_inv,y_cord + 1) = color1;
        // bottom right quad
        display->Pixel(x_cord_inv,y_cord_inv) = color1;
        display->Pixel(x_cord_inv,y_cord_inv - 1) = color1;
        // bottom left quad
        display->Pixel(x_cord,y_cord_inv) = color1;
        display->Pixel(x_cord,y_cord_inv - 1) = color1;
    }

  }
};

}  // namespace animation
}  // namespace kss
