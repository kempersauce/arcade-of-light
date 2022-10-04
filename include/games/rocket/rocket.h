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
  static constexpr uint8_t height{4};

  // colors (RGB)
  CRGB color;

  RocketBoost boost;

  /**
   * Rocket Constructor
   * @param loc - location on LED strip
   * @param clr - Color of the rocket ship
   */
  Rocket(size_t strip_length, CRGB color)
      : Animation(), color{color}, boost{5} {
    // Init physics settings
    physics.LocationMax = strip_length;
    physics.BounceFactor = -0.7;
    physics.ExplodeVelocity = 50;
    physics.ThrustMax = 100;

    Reset();
  }

  void Reset() { physics.Reset(); }

  void SetGravity(float gravity) { physics.gravity.y = gravity; }

  void Move() override {
    physics.Move();

    // Update boost location
    boost.loc = physics.location.y;
    boost.boostFactor = physics.thrust.y / physics.ThrustMax;
  }

  void Draw(display::Display* display) {
    // Draw the rocket ship
    const size_t middleStrip = display->size.width / 2;
    for (size_t i = max(ceil(physics.location.y), 0);
         i < min(physics.location.y + height, display->size.height); ++i) {
      display->Pixel(middleStrip, i) = color;
    }

    // dither rocket nose
    display->DitherPixelY(middleStrip, physics.location.y + height - 1, color);

    // dither rocket tail
    display->DitherPixelY(middleStrip, physics.location.y, color);

    // Draw the rocket boost
    boost.Draw(display);
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
