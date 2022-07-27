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
    int xLoc = physics.xLocation;
    for (int x = max(xLoc - 1, 0); x < min(xLoc + 2, display->numStrips); x++) {
      display->strips[x][(int)physics.Location] = CRGB::Magenta;
    }
  }
};

}  // namespace shooter
}  // namespace games
}  // namespace kss
