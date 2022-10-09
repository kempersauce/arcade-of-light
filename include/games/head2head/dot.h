#pragma once

#include "animation/animation.h"   // for Animation
#include "display/display.h"       // for Display
#include "engines/noise.h"         // for NoiseGenerator
#include "engines/physics_info.h"  // for PhysicsInfo
#include "math/random.h"           // for random::*
#include "math/vector2d.h"         // for Dimension

namespace kss {
namespace games {
namespace h2h {

class H2HDot : public animation::Animation {
  static constexpr uint8_t bleed_size{9};
  static constexpr uint8_t tail_length{5};
  static constexpr float fast_threshold{50};

  engines::NoiseGenerator noise{{1, bleed_size}, 200};  // fast small noise

 public:
  engines::PhysicsInfo physics;
  const CRGB color;
  const CRGB fast_color;

  H2HDot(CRGB color, CRGB fast_color)
      : Animation(), color{color}, fast_color{fast_color} {
    noise.scale = 4011;  // zoomed out shimery idk
  }

  void DropAt(math::Dimension location) {
    physics.Reset();
    physics.location = location;

    // randomly start in different directions
    if (math::random::Bool()) {
      physics.velocity.y = 20;
    } else {
      physics.velocity.y = -20;
    }
  }

  void Move() override {
    physics.Move();
    if (abs(physics.velocity.y) >= fast_threshold) {
      noise.fillnoise8();
    }
  }

  void setVelocity(float velocity) { physics.velocity.y = velocity; }

  inline bool IsFast() const {
    return abs(physics.velocity.y) >= fast_threshold;
  }

  void Draw(display::Display* display) override {
    if (IsFast()) {
      const bool going_up = physics.velocity.y > 0;

      // Glitch tail
      for (size_t i = 0; i < bleed_size; ++i) {
        uint8_t data = noise.Data(0, i);
        if (data >= 196) {
          size_t y;
          if (going_up) {
            y = physics.location.y - i;
          } else {
            y = physics.location.y + i;
          }
          display->BlendPixel(physics.location.x, y, color,
                              (data / 4 + 196) / 255.0f);
        }
      }

      // Shadow tail
      for (size_t i = 0; i < tail_length; ++i) {
        const float blend_coef = 1 - (float)i / (float)tail_length;
        if (going_up) {
          display->BlendPixel(physics.location.x, physics.location.y - i,
                              fast_color, blend_coef);
        } else {
          display->BlendPixel(physics.location.x, physics.location.y + i,
                              fast_color, blend_coef);
        }
      }
    }

    // Draw the dot
    display->DitherPixelY(physics.location.x, physics.location.y, color);
  }
};

}  // namespace h2h
}  // namespace games
}  // namespace kss
