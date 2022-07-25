#pragma once

/*
SkyFade class
Draws a blue color,
fading back to the original color a third of the way up
*/

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

class SkyFade : public kss::animation::Animation {
 private:
  CRGB* blendColor;

 public:
  SkyFade(CRGB* fadeColor) { blendColor = fadeColor; }

  void setFadeColor(CRGB* fadeColor) { blendColor = fadeColor; }

  void draw(Display* display) {
    int heightMax = display->lengthStrips / 3;  // only go a third of the way up
    for (int i = 0; i < display->numStrips; i++) {
      for (int j = 0; j < heightMax; j++) {
        float blueFactor = ((float)(heightMax - j)) / ((float)heightMax);
        display->blendPixel(i, j, blendColor, blueFactor);
      }
    }
  }
};
