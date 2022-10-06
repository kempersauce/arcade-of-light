#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "math/sine.h"            // for SineWaveGenerator
#include "math/vector2d.h"        // for Vector2D

namespace kss {
namespace animation {

class WaveOut : public Animation {
  math::SineWaveGenerator wave;

 public:
  uint8_t hue;

  WaveOut(uint8_t hue) : Animation(), wave{10, 1, -.01}, hue{hue} {}

  void Move() override { wave.Move(); }

  void Draw(display::Display* display) override {
    const math::Vector2D<float> center{0, display->size.height / 2.0f};
    for (size_t x = 0; x < display->size.x; ++x) {
      math::Vector2D<float> dist{center.x - (float)x, 0};
      for (size_t y = 0; y < display->size.y; ++y) {
        dist.y = center.y - (float)y;
        const uint8_t val = (wave.GetVal(dist.GetMagnitude()) + 1.0f) * 128;
        display->Pixel(x, y).setHSV(hue, 255, val);
      }
    }
  }
};

class WaveOut2 : public Animation {
  math::SineWaveGenerator wave;

 public:
  uint8_t hue;

  WaveOut2(uint8_t hue) : Animation(), wave{10, 1, -.01}, hue{hue} {}

  void Move() override { wave.Move(); }

  void Draw(display::Display* display) override {
    const math::Vector2D<float> center_a{display->size.width - 1, 0.0f};
    const math::Vector2D<float> center_b{display->size.width - 1,
                                         display->size.height};
    for (size_t x = 0; x < display->size.x; ++x) {
      math::Vector2D<float> dist_a{center_a.x - (float)x, 0};
      math::Vector2D<float> dist_b{center_b.x - (float)x, 0};
      for (size_t y = 0; y < display->size.y; ++y) {
        dist_a.y = center_a.y - (float)y;
        dist_b.y = center_b.y - (float)y;
        const uint8_t val = (wave.GetVal(dist_a.GetMagnitude()) / 2 +
                             wave.GetVal(dist_b.GetMagnitude()) / 2 + 1.0f) *
                            128;
        display->Pixel(x, y).setHSV(hue, 255, val);
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
