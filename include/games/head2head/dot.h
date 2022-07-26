#pragma once

#include <FastLED.h>

#include "animation/animation.h"   // for Animation
#include "display/display.h"       // for kss::display::Display
#include "engines/physics_info.h"  // for PhysicsInfo

class H2HDot : public kss::animation::Animation {
 public:
  kss::engines::PhysicsInfo physics;
  CRGB color;

  H2HDot(CRGB startColor, int stripIndex) : Animation(), physics() {
    color = startColor;
    physics.xLocation = stripIndex;
  }

  void Move() { physics.Move(); }

  void setVelocity(float velocity) { physics.Velocity = (int)velocity; }

  void draw(kss::display::Display* display) {
    // Don't draw outside the display boundaries
    if (physics.HasHitEdge == false) {
      display->ditherPixel((int)physics.xLocation, physics.Location, &color);
    }
  }
};
