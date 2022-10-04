#pragma once

#include "animation/animation.h"   // for Animation
#include "display/display.h"       // for Display
#include "engines/physics_info.h"  // for PhysicsInfo

namespace kss {
namespace animation {

// Single color background
class WavePulse : public Animation {
  const size_t width;
  const CRGB color;

 public:
  engines::PhysicsBasic physics;

  WavePulse(size_t width, CRGB color)
      : Animation(), width{width}, color{color} {}

  void Move() override { physics.Move(); }

  void Draw(display::Display* display) {
    // Do <= here to get a full 1.0 blend at the front
    for (size_t i = 0; i <= width; ++i) {
      const float presence = (float)i / (float)width;
      for (size_t x = 0; x < display->size.width; ++x) {
        display->BlendPixel(x, physics.location.y + i, color, presence);
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
