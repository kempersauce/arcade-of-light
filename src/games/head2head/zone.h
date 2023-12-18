#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace games {
namespace h2h {

class H2HZone : public animation::Animation {
 public:
  const CRGB color;

  const size_t xLoc;
  const size_t yMin;
  const size_t yMax;

  bool upsideDown;

  H2HZone(CRGB color, size_t xLocation, size_t yMinimum, size_t yMaximum,
          bool isTop)
      : Animation(),
        color{color},
        xLoc{xLocation},
        yMin{yMinimum},
        yMax{yMaximum},
        upsideDown{isTop} {}

  inline bool checkZone(int y) const { return y >= yMin && y <= yMax; }

  // returns 0.0 to 1.0 based on how far into the zone the dot is
  float zoneDepth(int y) const {
    if (checkZone(y) == false) {
      return 0;
    }

    const float range = yMax - yMin;

    // BOTTOM - SPECIFIC CALCULATION
    if (upsideDown) {
      return (float)(y - yMin) / range;
    } else {
      return (float)(yMax - y) / range;
    }
  }

  void Draw(display::Display* display) override {
    for (size_t y = yMin + 1; y < yMax; ++y) {
      display->Pixel(xLoc, y).fadeToBlackBy(255 * zoneDepth(y));
    }
    display->Pixel(xLoc, yMin) = color;
    display->Pixel(xLoc, yMax) = color;
  }
};

}  // namespace h2h
}  // namespace games
}  // namespace kss
