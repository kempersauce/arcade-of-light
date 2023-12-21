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
  CRGB current_color;
  const size_t center_x;
  size_t center_y;
  const size_t slope = 2;
  const size_t y_min = 30;
  const size_t y_max = 130;

 public:
  Diamond(int center_x, int height, int width, CRGB color1, CRGB color2)
      : Animation(),
        center_x{center_x},
        center_y{center_y},
        height{height},
        width{width},
        color1{color1},
        color2{color2} {
    center_y = (y_max + y_min) / 2;
  }

  const size_t thickness = 2;

  void Draw(display::Display* display) {
    // working but basic
    // for (size_t x = 0; x <= (width)/2 ; ++x) {
    //     Debug(x);
    //     size_t x_cord = x;
    //     size_t y_cord = center_y + x * slope;
    //     size_t y_cord_inv = center_y - x * slope;
    //     size_t x_cord_inv = center_x - x + width/2 - 2;
    //     // top left quad
    //     display->Pixel(x_cord,y_cord) = color1;
    //     display->Pixel(x_cord,y_cord + 1) = color1;
    //     // top right quad
    //     display->Pixel(x_cord_inv,y_cord) = color1;
    //     display->Pixel(x_cord_inv,y_cord + 1) = color1;
    //     // bottom right quad
    //     display->Pixel(x_cord_inv,y_cord_inv) = color1;
    //     display->Pixel(x_cord_inv,y_cord_inv - 1) = color1;
    //     // bottom left quad
    //     display->Pixel(x_cord,y_cord_inv) = color1;
    //     display->Pixel(x_cord,y_cord_inv - 1) = color1;
    // }
    for (size_t x = 0; x <= 5; ++x) {
      PatternWave(display, x, x);
    }
  }

  void PatternWave(display::Display* display, int x, int y_offset) {
    size_t y_diff = y_offset;
    ++y_diff;
    if (y_diff == 4 || y_diff == 3) {
      current_color = color1;
    } else if (y_diff == 5) {
      y_diff = 0;
      current_color = color2;
    } else {
      current_color = CRGB::Black;
    }
    for (size_t y = y_min; y <= center_y; ++y) {
      display->Pixel(x, y + y_offset) = current_color;
    }
  }
};

}  // namespace animation
}  // namespace kss
