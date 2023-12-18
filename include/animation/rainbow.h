#pragma once

#include <FastLED.h>  // for CHSV

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

// Rainbow Animation
class Rainbow : public Animation {
 public:
  // override rainbow Draw function
  void Draw(display::Display* display) {
    const float hue_factor = 256.0f / display->size.height;
    for (size_t x = 0; x < display->size.x; ++x) {
      for (size_t y = 0; y < display->size.y; ++y) {
        const uint8_t hue = y * hue_factor;
        display->Pixel(x, y).setHSV(hue, 255, 255);
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
