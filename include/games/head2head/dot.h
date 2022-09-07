#pragma once

#include <FastLED.h>

#include "animation/animation.h"   // for Animation
#include "display/display.h"       // for Display
#include "engines/physics_info.h"  // for PhysicsInfo

namespace kss {
namespace games {
namespace h2h {

class H2HDot : public animation::Animation {
 public:
  engines::PhysicsInfo physics;
  CRGB color;

  H2HDot(CRGB startColor, size_t stripIndex) : Animation(), physics() {
    color = startColor;
    physics.location.x = stripIndex;
  }

  virtual void Move() override { physics.Move(); }

  void setVelocity(float velocity) { physics.velocity.y = (int)velocity; }

  void draw(display::Display& display) {
    // Don't draw outside the display boundaries
    if (physics.HasHitEdge == false) {
      display.DitherPixel((int)physics.location.x, physics.location.y, &color);
    }
  }
};

}  // namespace h2h
}  // namespace games
}  // namespace kss
