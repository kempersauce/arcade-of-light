// Rocket Class
// Class that sets a dot in a specific locatio on the LED strip

#pragma once

#include "animation/animation.h"        // for Animation
#include "display/display.h"            // for Display
#include "engines/physics_info.h"       // for PhysicsInfo
#include "games/rocket/rocket_boost.h"  // for RocketBoost

namespace kss {
namespace games {
namespace rocket {

class Rocket : public animation::Animation {
 public:
  engines::PhysicsInfo physics;

  // Rocket constants
  // int Mass = 2;
  int Height = 2;
  // int Gravity; // this gets set according to the level

  // colors (RGB)
  CRGB* color;

  // Rocket State
  // float Thrust;
  // float ThrustMax = 200;
  // float Acceleration;
  // float Velocity;
  // float ExploadVelocity = 50;
  // float Location;
  // int LocationMax;
  // long Time;
  // bool Exploded;

  RocketBoost boost;

  /**
   * Rocket Constructor
   * @param loc - location on LED strip
   * @param clr - Color of the rocket ship
   */
  Rocket(int lengthStrips, CRGB* clr) : Animation(), physics(), boost(5) {
    // Init physics settings
    physics.LocationMax = lengthStrips;
    physics.BounceFactor = -0.7;
    physics.ExplodeVelocity = 50;
    physics.ThrustMax = 200;
    physics.Mass = 2;

    color = clr;
    Reset();
  }

  void Reset() { physics.Reset(); }

  void SetGravity(int gravity) { physics.Gravity = gravity; }

  void SetBoost(int thrustLevel) { physics.Thrust = thrustLevel; }

  void Move(bool respectEdges = true) {
    physics.Move(respectEdges);

    // Update boost location
    boost.loc = physics.Location;
    boost.boostFactor = physics.Thrust / physics.ThrustMax;
  }

  void draw(display::Display* display) {
    // Draw the rocket ship
    int middleStrip = display->numStrips / 2;
    for (int i = max(ceil(physics.Location), 0);
         i < min((int)physics.Location + Height, display->lengthStrips); i++) {
      display->strips[middleStrip][i] = *color;
    }
    display->ditherPixel(middleStrip, physics.Location + Height - 1,
                         color);  // dither rocket nose
    display->ditherPixel(middleStrip, physics.Location,
                         color);  // dither rocket tail

    // Draw the rocket boost
    boost.draw(display);
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
