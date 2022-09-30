#pragma once

#include <pixeltypes.h>  // for CRGB

#include "animation/animation.h"   // for Animation
#include "engines/physics_info.h"  // for PhysicsInfo
#include "math/vector2d.h"         // for Vector2D

namespace kss {
namespace animation {

namespace _circle {
constexpr float grid_spacing_x{2.125};
constexpr float grid_spacing_y{0.65};
const math::Vector2D<float> grid_spacing{_circle::grid_spacing_x,
                                         _circle::grid_spacing_y};
}  // namespace _circle

class Circle : public Animation {
  const float radius;

 public:
  engines::PhysicsInfo physics;
  CRGB color;
  Circle(float radius, CRGB color)
      : Animation(), radius{radius}, color{color} {}

 private:
  inline size_t GetStartX() {
    if (physics.location.x <= radius) {
      return 0;
    }
  }

 public:
  void Move() override { physics.Move(); }

  void Draw(display::Display* display) override {
    math::Vector2D<float> box_size_px = radius / _circle::grid_spacing;
    math::Vector2D<int> start = (physics.location - box_size_px).GetAs<int>();
    math::Vector2D<int> end = (physics.location + box_size_px + 1).GetAs<int>();
    for (size_t x = max(0, start.x); x < end.x; ++x) {
      for (size_t y = max(0, start.y); y < end.y; ++y) {
        if (!display->IsInBounds(x, y)) {
          continue;
        }

        // get hypotenuse
        math::Vector2D<float> distance_px{abs(physics.location.x - x),
                                          abs(physics.location.y - y)};
        float distance_in =
            (distance_px * _circle::grid_spacing).GetMagnitude();
        if (distance_in <= radius) {
          display->Pixel(x, y) = color;
        } else {
          const float overshoot_in = distance_in - radius;

          // TODO this is a bit fuzzy, we assume max distance each time
          // even on x & y axis
          const float overshoot_px =
              (overshoot_in / _circle::grid_spacing).GetMagnitude();
          if (overshoot_px <= 1) {
            display->BlendPixel(x, y, &color, 1-overshoot_px);
          }
        }
      }
    }
  }
};

}  // namespace animation
}  // namespace kss