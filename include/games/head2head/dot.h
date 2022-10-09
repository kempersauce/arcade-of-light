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
  static constexpr float fast_threshold{50};

  engines::NoiseGenerator noise{{1, bleed_size}, 200};  // fast small noise

 public:
  engines::PhysicsInfo physics;
  const CRGB color;
  const CRGB fast_color;

  H2HDot(CRGB color, CRGB fast_color, size_t stripIndex)
      : Animation(), color{color}, fast_color{fast_color} {
    physics.location.x = stripIndex;
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

  bool every_other = false;
  void Draw(display::Display* display) override {
    if (IsFast()) {
      const int8_t direction = physics.velocity.y > 0 ? -1 : 1;
      // Glitch tail
      for (size_t i = 0; i < bleed_size; ++i) {
        uint8_t data = noise.Data(0, i);
        if (data >= 196) {
          const size_t y = physics.location.y + direction * i;
          display->BlendPixel(physics.location.x, y, color,
                              (data / 4 + 196) / 255.0f);
        }
      }

      display->DitherPixelY(physics.location.x, physics.location.y + direction,
                            fast_color);
      display->DitherPixelY(physics.location.x, physics.location.y, color);
    } else {
      display->DitherPixelY(physics.location.x, physics.location.y, color);
    }
  }
};

}  // namespace h2h
}  // namespace games
}  // namespace kss
