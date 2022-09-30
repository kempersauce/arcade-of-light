#pragma once

#include "animation/animation.h"   // for Animation
#include "engines/physics_info.h"  // for PhysicsInfo

namespace kss {
namespace animation {

namespace _circle {
constexpr float grid_spacing_x{0};
constexpr float grid_spacing_y{0.65};
}  // namespace _circle

class Circle : public Animation {
  engines::PhysicsInfo physics;

 public:
  Circle(uint8_t radius, CRGB hue) : Animation() {}

  void Move() override {}
  void Draw(display::Display* display) override {}
};

}  // namespace animation
}  // namespace kss