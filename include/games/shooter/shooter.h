#pragma once

#include "animation/animation.h"   // for Animation
#include "display/display.h"       // for Display
#include "engines/physics_info.h"  // for PhysicsInfo

namespace kss {
namespace games {
namespace shooter {

class Shooter : public animation::Animation {
 public:
  engines::PhysicsInfo physics;

  Shooter() : Animation(), physics() {}

  void draw(display::Display* display) {
    int xLoc = physics.location.x;
    for (int x = max(xLoc - 1, 0); x < min(xLoc + 2, display->strip_count);
         x++) {
      display->Pixel(x, (int)physics.location.y) = CRGB::Magenta;
    }
  }
};

}  // namespace shooter
}  // namespace games
}  // namespace kss
