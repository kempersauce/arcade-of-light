#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

class Charge : Animation {
 public:
  // location values
  int xStart;
  int xLoc;
  int yStart;
  int yLoc;
  // boundaries of movement Area
  int xMax;
  int yMax;
  // colors (HSV)
  int Hue;
  int Saturation;
  int Brightness;

  // Constructor
  Charge(int startHue, int startX, int startY, int yMaximum) {
    Hue = startHue;
    Saturation = 255;
    Brightness = 200;
    xStart = startX;
    xLoc = startX;
    yStart = startY;
    yLoc = startY;
    yMax = yMaximum;
  }

  // Methods
  void power(bool powerUp) {
    if (yStart < yMax) {
      if (powerUp == true) {
        if (yLoc > yMax) {
          yLoc++;
        }
        // Saturation = 255 * (yLoc / yMax);
      } else {
        if (yLoc > 0) {
          yLoc--;
        }
        // Saturation = 255 * (yLoc / yMax);
      }
    } else {
      if (powerUp == true) {
        if (yLoc < yMax) {
          yLoc--;
        }
        // Saturation = 255 * (yLoc / yMax);
      } else {
        if (yLoc < 0) {
          yLoc--;
        }
        // Saturation = 255 * (yLoc / yMax);
      }
    }
  }

  void draw(display::Display& display) {
    if (yStart < yMax) {
      for (int i = yStart; i < yLoc; i++) {
        display.Pixel(xLoc, i) = CHSV(Hue, Saturation, Brightness);
      }
    } else {
      for (int i = yStart; i > yLoc; i--) {
        display.Pixel(xLoc, i) = CHSV(Hue, Saturation, Brightness);
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
