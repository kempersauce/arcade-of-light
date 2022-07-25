#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for display::Display

namespace kss {
namespace animation {

// Dot Class
// Class that sets a dot in a specific locatio on the LED strip
class Dot : public Animation {
 public:
  // location values
  int xLoc;
  int yLoc;
  // boundaries of movement Area
  int xMax;
  int yMax;
  // colors (RGB)
  CRGB color;

  // Constructor - COULD BE MORE EFFICIENT
  Dot(CRGB startColor, int startX, int startY, int xMaximum, int yMaximum) {
    color = startColor;
    xLoc = startX;
    yLoc = startY;
    xMax = xMaximum;
    yMax = yMaximum;
  }

  // Methods
  void move(int xMove, int yMove) {
    xLoc += xMove;
    yLoc += yMove;
    if (xLoc > xMax) {
      xLoc = xMax;
    }
    if (yLoc > yMax) {
      yLoc = yMax;
    }
    if (xLoc < 0) {
      xLoc = 0;
    }
    if (yLoc < 0) {
      yLoc = 0;
    }
  }

  void changeColor(CRGB newColor) { color = newColor; }

  void draw(display::Display* display) { display->strips[xLoc][yLoc] = color; }
};

}  // namespace animation
}  // namespace kss
