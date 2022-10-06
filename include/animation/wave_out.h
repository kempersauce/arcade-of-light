#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "math/sine.h"            // for SineWaveGenerator
#include "math/vector2d.h"        // for Vector2D

namespace kss {
namespace animation {

namespace _wave_out {

class WaveOutBase : public Animation {
 public:
  static constexpr float SPEED_SLOW{-0.01f};
  static constexpr float SPEED_FAST{-0.04f};

  math::SineWaveGenerator wave;

  uint8_t hue;
  uint8_t sat;

  WaveOutBase(uint8_t hue, uint8_t sat)
      : Animation(), wave{10, 1, SPEED_SLOW}, hue{hue}, sat{sat} {}
  virtual ~WaveOutBase() = default;

  void Move() override { wave.Move(); }
};

}  // namespace _wave_out

class WaveOut : public _wave_out::WaveOutBase {
 public:
  WaveOut(uint8_t hue, uint8_t sat = 255) : WaveOutBase(hue, sat) {}

  void Draw(display::Display* display) override {
    const math::Vector2D<float> center{0, display->size.height / 2.0f};
    for (size_t x = 0; x < display->size.x; ++x) {
      math::Vector2D<float> dist{center.x - (float)x, 0};
      for (size_t y = 0; y < display->size.y; ++y) {
        dist.y = center.y - (float)y;
        const uint8_t val = (wave.GetVal(dist.GetMagnitude()) + 1.0f) * 128;
        display->Pixel(x, y).setHSV(hue, sat, val);
      }
    }
  }
};

class WaveOut2 : public _wave_out::WaveOutBase {
 public:
  WaveOut2(uint8_t hue, uint8_t sat = 255) : WaveOutBase(hue, sat) {}

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
        display->Pixel(x, y).setHSV(hue, sat, val);
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
