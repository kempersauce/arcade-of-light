#pragma once

#include <vector>  // for std::vector

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "math/sine.h"            // for SineWaveGenerator
#include "math/vector2d.h"        // for Vector2D

namespace kss {
namespace animation {

namespace _wave_out {

struct WaveSource {
  math::Vector2D<float> location;
  bool is_square;
  WaveSource(math::Vector2D<float> location, bool is_square)
      : location{location}, is_square{is_square} {}
};

}  // namespace _wave_out

class WaveOut : public Animation {
 public:
  static constexpr float SPEED_SLOW{-0.01f};
  static constexpr float SPEED_FAST{-0.04f};

  math::SineWaveGenerator wave;

  uint8_t hue;
  uint8_t sat;

  std::vector<_wave_out::WaveSource> sources;

  WaveOut(uint8_t hue, uint8_t sat)
      : Animation(), wave{10, 1, SPEED_SLOW}, hue{hue}, sat{sat} {}
  virtual ~WaveOut() = default;

 protected:
  inline float GetVal(const math::Vector2D<float> dist) const {
    return wave.GetVal(dist.GetMagnitude());
  }

  inline float GetSquareVal(const math::Vector2D<float> dist) const {
    const math::Vector2D<float> dist_abs{dist.GetAbs()};
    return wave.GetVal(max(dist_abs.x, dist_abs.y));
  }

 public:
  void Move() override { wave.Move(); }

  void AddSource(math::Vector2D<float> location) {
    sources.emplace_back(location, false);
  }

  void AddSquareSource(math::Vector2D<float> location) {
    sources.emplace_back(location, true);
  }

  void Draw(display::Display* display) override {
    const math::Vector2D<float> center_a{display->size.width - 1, 0.0f};
    const math::Vector2D<float> center_b{display->size.width - 1,
                                         display->size.height - 1};
    for (size_t x = 0; x < display->size.x; ++x) {
      for (size_t y = 0; y < display->size.y; ++y) {
        float total = 0;
        for (const _wave_out::WaveSource& source : sources) {
          const math::Vector2D<float> dist{
              display->grid_scale *
              (source.location - math::Vector2D<float>{x, y})};
          total += (source.is_square ? GetSquareVal(dist) : GetVal(dist));
        }
        const uint8_t val = (total / sources.size() + 1.0f) * 128;
        display->Pixel(x, y).setHSV(hue, sat, val);
      }
    }
  }
};

class WaveOut1 : public WaveOut {
 public:
  WaveOut1(uint8_t hue, uint8_t sat, math::Dimension display_size)
      : WaveOut(hue, sat) {
    AddSource({0, (display_size.height - 1) / 2.0f});
  }
};

class WaveOut2 : public WaveOut {
 public:
  WaveOut2(uint8_t hue, uint8_t sat, math::Dimension display_size)
      : WaveOut(hue, sat) {
    AddSource({display_size.width - 1, 0.0f});
    AddSource({display_size.width - 1, display_size.height - 1});
  }
};

class WaveOut3 : public WaveOut {
 public:
  WaveOut3(uint8_t hue, uint8_t sat, math::Dimension display_size)
      : WaveOut(hue, sat) {
    AddSource({(display_size.width - 1) / 2.0f,
               (display_size.height - 1) * 3.0f / 5.0f});  // golden ratio
    wave.wavelength = display_size.height / 27.0f;
  }
};

class WaveOut4 : public WaveOut {
 public:
  WaveOut4(uint8_t hue, uint8_t sat, math::Dimension display_size)
      : WaveOut(hue, sat) {
    AddSource((display_size - 1) / 2.0f);
    wave.wavelength = display_size.height / 18.0f;
  }
};

}  // namespace animation
}  // namespace kss
