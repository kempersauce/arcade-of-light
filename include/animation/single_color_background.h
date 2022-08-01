#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

// Single color background
class SingleColorBG : public Animation {
 public:
  // colors (RGB)
  int red;
  int green;
  int blue;

  SingleColorBG(int redColor, int greenColor, int blueColor) : Animation() {
    red = redColor;
    green = greenColor;
    blue = blueColor;
  }

  void setColor(int redColor, int greenColor, int blueColor) {
    red = redColor;
    green = greenColor;
    blue = blueColor;
  }

  void draw(display::Display* display) {
    for (int i = 0; i < display->lengthStrips; i++) {
      for (int j = 0; j < display->numStrips; j++) {
        display->Pixel(j, i).setRGB(red, green, blue);
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
