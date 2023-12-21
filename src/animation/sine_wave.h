#pragma once

#include <math.h>  // for fmod

#include <vector>  // for std::vector

#include "animation/animation.h"  // for Animation
#include "math/sine.h"            // for SineWaveGeneratorRamped
#include "serial/debug.h"         // for Debug

namespace kss {
namespace animation {

class SineWave : public Animation {
 public:
  CRGB color;
  float opacity;
  std::vector<math::SineWaveGeneratorRamped> waves;

  SineWave(CRGB color, float opacity = 1.0f)
      : Animation(), color{color}, opacity{opacity} {}

  void Move() override {
    for (auto& wave : waves) {
      wave.Move();
    }
  }

  void Draw(display::Display* display) override {
    const float midpoint = (float)(display->size.x - 1) / 2;
    for (size_t y = 0; y < display->size.y; ++y) {
      float x = midpoint;
      for (auto& wave : waves) {
        x += wave.GetVal(y);
      }
      display->DitherPixelX(x, y, color, opacity);
    }
  }
};

}  // namespace animation
}  // namespace kss
