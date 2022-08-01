#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace games {
namespace h2h {

class H2HZone : public animation::Animation {
 public:
  CRGB color;
  int yMin;
  int yMax;
  int xLoc;

  bool upsideDown;

  H2HZone(CRGB startColor, int xLocation, int yMinimum, int yMaximum,
          bool isTop) {
    color = startColor;
    xLoc = xLocation;
    yMin = yMinimum;
    yMax = yMaximum;

    upsideDown = isTop;
  }

  bool checkZone(int y) { return y >= yMin && y <= yMax; }

  // returns 0.0 to 1.0 based on how far into the zone the dot is
  float zoneDepth(int y) {
    if (checkZone(y) == false) {
      return 0;
    }

    float range = yMax - yMin;

    // BOTTOM - SPECIFIC CALCULATION
    if (upsideDown) {
      return (float)(y - yMin) / range;
    } else {
      return (float)(yMax - y) / range;
    }
  }

  void draw(display::Display* display) {
    display->Pixel(xLoc, yMin) = CRGB::White;
    display->Pixel(xLoc, yMax) = CRGB::White;
  }
};

}  // namespace h2h
}  // namespace games
}  // namespace kss
