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
 private:
  CRGB* blendColor;

 public:
  SkyFade(CRGB* fadeColor) { blendColor = fadeColor; }

  void setFadeColor(CRGB* fadeColor) { blendColor = fadeColor; }

  void draw(display::Display* display) {
    const size_t heightMax =
        display->strip_length / 3;  // only go a third of the way up
    for (size_t i = 0; i < display->strip_count; i++) {
      for (int j = 0; j < heightMax; j++) {
        float blueFactor = ((float)(heightMax - j)) / ((float)heightMax);
        display->BlendPixel(i, j, blendColor, blueFactor);
      }
    }
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
