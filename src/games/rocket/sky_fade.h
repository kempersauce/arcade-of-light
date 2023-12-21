#pragma once

/*
SkyFade class
Draws a blue color,
fading back to the original color a third of the way up
*/

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace games {
namespace rocket {

class SkyFade : public animation::Animation {
 public:
  CRGB color;
  SkyFade(CRGB fadeColor) : Animation(), color{color} {}

  void Draw(display::Display* display) override {
    const size_t heightMax =
        display->size.y / 3;  // only go a third of the way up
    for (size_t i = 0; i < display->size.x; i++) {
      for (size_t j = 0; j < heightMax; j++) {
        float blueFactor = ((float)(heightMax - j)) / ((float)heightMax);
        display->BlendPixel(i, j, color, blueFactor);
      }
    }
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
