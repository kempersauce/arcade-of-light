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

  RocketBoost boost;

  /**
   * Rocket Constructor
   * @param loc - location on LED strip
   * @param clr - Color of the rocket ship
   */
  Rocket(int strip_length, CRGB* clr) : Animation(), physics(), boost(5) {
    // Init physics settings
    physics.LocationMax = strip_length;
    physics.BounceFactor = -0.7;
    physics.ExplodeVelocity = 50;
    physics.ThrustMax = 200;
    physics.Mass = 2;

    color = clr;
    Reset();
  }

  void Reset() { physics.Reset(); }

  void SetGravity(float gravity) { physics.gravity.y = gravity; }

  void SetBoost(float thrustLevel) { physics.thrust.y = thrustLevel; }

  virtual void Move() override {
    physics.Move();

    // Update boost location
    boost.loc = physics.location.y;
    boost.boostFactor = physics.thrust.y / physics.ThrustMax;
  }

  void draw(display::Display& display) {
    // Draw the rocket ship
    const size_t middleStrip = display.size.x / 2;
    for (size_t i = max(ceil(physics.location.y), 0);
         i < min((int)physics.location.y + Height, display.size.y);
         i++) {
      display.Pixel(middleStrip, i) = *color;
    }
    display.DitherPixel(middleStrip, physics.location.y + Height - 1,
                         color);  // dither rocket nose
    display.DitherPixel(middleStrip, physics.location.y,
                         color);  // dither rocket tail

    // Draw the rocket boost
    boost.draw(display);
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
