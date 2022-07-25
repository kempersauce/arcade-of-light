#pragma once

#include "animation/animation.h"   // for Animation
#include "display/display.h"       // for Display
#include "engines/physics_info.h"  // for PhysicsInfo

class Shooter : public kss::animation::Animation {
 public:
  PhysicsInfo physics;

  Shooter() : Animation(), physics() {}

  void draw(Display* display) {
    int xLoc = physics.xLocation;
    for (int x = max(xLoc - 1, 0); x < min(xLoc + 2, display->numStrips); x++) {
      display->strips[x][(int)physics.Location] = CRGB::Magenta;
    }
  }
};
