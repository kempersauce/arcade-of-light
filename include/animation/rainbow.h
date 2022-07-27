#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

// Rainbow Animation
class RainbowAni : public Animation {
 public:
  // override rainbow draw function
  void draw(display::Display* display) {
    for (int i = 1; i < display->lengthStrips; i++) {
      for (int j = 0; j < display->numStrips; j++) {
        display->strips[j][i] = rainbows[(i % 7) + iterator];
      }
    }

    if (iterator < 6) {
      iterator++;
    } else {
      iterator = 0;
    }
  }

 private:
  CRGB rainbows[14] = {CRGB::Red,    CRGB::Orange, CRGB::Yellow, CRGB::Green,
                       CRGB::Blue,   CRGB::Indigo, CRGB::Violet, CRGB::Red,
                       CRGB::Orange, CRGB::Yellow, CRGB::Green,  CRGB::Blue,
                       CRGB::Indigo, CRGB::Violet};

  int iterator = 0;
};

}  // namespace animation
}  // namespace kss
