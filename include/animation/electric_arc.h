
#pragma once

#include <vector>

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "math/random.h"          // for random::*
#include "time/now.h"             // for Now

namespace kss {
namespace animation {

class ElectricArc : public Animation {
  static constexpr uint32_t update_speed{33};
  const size_t width;
  const CRGB color;
  uint32_t last_changed{0};

 public:
  std::vector<size_t> arc;
  size_t yLocation;
  size_t magnitude = 2;

  ElectricArc(size_t width, CRGB color)
      : Animation(), width{width}, color{color} {}

  void Move() override {
    const uint32_t now = time::Now();
    if (now - last_changed >= update_speed) {
      last_changed = now;
      do {
        arc.clear();
        arc.push_back(yLocation);
        for (size_t y = yLocation, x = 1; x < width; x++) {
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
    }
  }

  void Draw(display::Display* display) override {
    for (size_t i = 0; i < arc.size(); i++) {
      size_t arcHeight = arc[i];
      display->Pixel(i, arcHeight) = color;

      arcHeight++;
      display->Pixel(i, arcHeight) = color;
    }
  }
};

}  // namespace animation
}  // namespace kss
