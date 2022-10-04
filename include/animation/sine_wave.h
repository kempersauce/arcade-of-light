#pragma once

#include <math.h>  // for fmod

#include <vector>  // for std::vector

#include "animation/animation.h"  // for Animation
#include "serial/debug.h"         // for Debug

namespace kss {
namespace animation {

class SineWaveGenerator {
  float distance_offset{0};
  bool is_active{false};

 public:
  // sine wavelength in pixels
  float wavelength;
  float amplitude;

  // pixels per millisecond
  float speed;

  SineWaveGenerator(float wavelength, float amplitude, float speed)
      : wavelength{wavelength}, amplitude{amplitude}, speed{speed} {}

  void On() { is_active = true; }
  void Off() { is_active = false; }

  void Move() {
    if (!is_active) {
      return;
    }
    distance_offset =
        fmod(distance_offset + time::LoopElapsedMillis() * speed, wavelength);
  }

  float GetVal(const float distance) const {
    if (!is_active) {
      return 0;
    }
    float theta = fmod(1 + (distance + distance_offset) / wavelength, 1);
    const float sine = ((float)sin8(255.0f * theta) - 128.0f) / 128.0f;
    // const float sine = sin(TWO_PI * theta);
    return amplitude * sine;
  }
};

class SineWave : public Animation {
 public:
  CRGB color;
  float opacity;
  std::vector<SineWaveGenerator> waves;

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
