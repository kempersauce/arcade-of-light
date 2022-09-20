
#pragma once

#include <vector>

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "math/random.h"          // for random::*

namespace kss {
namespace animation {

class ElectricArc : public Animation {
  std::vector<size_t> arc;
  CRGB color = CRGB::Purple;

 public:
  size_t yLocation;
  size_t magnitude = 2;

  void draw(display::Display* display) override {
    do {
      arc.clear();
      arc.push_back(yLocation);
      for (size_t y = yLocation, x = 1; x < display->size.x; x++) {
        float r = math::random::Float();
        if (r <= 0.4) {  // bottom 40%
          y += magnitude;
        } else if (r >= 0.6) {  // top 40%
          y -= magnitude;
        } else {  // middle 20%
          // nothing
        }

        arc.push_back(y);
      }
    } while (arc.back() != yLocation);

    for (size_t i = 0; i < arc.size(); i++) {
      size_t arcHeight = arc[i];
      if (display->IsInBounds(i, arcHeight)) {
        display->Pixel(i, arcHeight) = CRGB::Purple;
      }

      arcHeight++;
      if (display->IsInBounds(i, arcHeight)) {
        display->Pixel(i, arcHeight) = CRGB::Purple;
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
