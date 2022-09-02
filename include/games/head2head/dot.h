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

  H2HDot(CRGB startColor, int stripIndex) : Animation(), physics() {
    color = startColor;
    physics.xLocation = stripIndex;
  }

  virtual void Move() override { physics.Move(); }

  void setVelocity(float velocity) { physics.Velocity = (int)velocity; }

  void draw(display::Display* display) {
    // Don't draw outside the display boundaries
    if (physics.HasHitEdge == false) {
      display->DitherPixel((int)physics.xLocation, physics.Location, &color);
    }
  }
};

}  // namespace h2h
}  // namespace games
}  // namespace kss
