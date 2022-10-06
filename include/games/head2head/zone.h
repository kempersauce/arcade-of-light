#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace games {
namespace h2h {

class H2HZone : public animation::Animation {
 public:
  const CRGB color;
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

  void Draw(display::Display* display) {
    display->Pixel(xLoc, yMin) = color;
    display->Pixel(xLoc, yMax) = color;
  }
};

}  // namespace h2h
}  // namespace games
}  // namespace kss
