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
  const size_t x;

 public:
  engines::PhysicsInfo physics;

  // Rocket constants
  static constexpr uint8_t height{4};

  // colors (RGB)
  CRGB color;
  bool super_boost{false};

  RocketBoost boost;
  RocketBoost super_boost_left;
  RocketBoost super_boost_right;

  static constexpr float ThrustMax = 100;

  /**
   * Rocket Constructor
   * @param loc - location on LED strip
   * @param clr - Color of the rocket ship
   */
  Rocket(math::Dimension display_size, CRGB color)
      : Animation(),
        x{display_size.width / 2},
        color{color},
        boost{7, x},
        super_boost_left{2, x - 1, .5},
        super_boost_right{2, x + 1, .5} {
    // Init physics settings
    physics.LocationMax = display_size.height;
    physics.BounceFactor = -0.7;
    physics.ExplodeVelocity = 50;

    Reset();
  }

  void Reset() {
    physics.Reset();
    physics.location.x = x;
    super_boost = false;
  }

  void SetGravity(float gravity) { physics.gravity.y = gravity; }

  void Move() override {
    if (!super_boost && physics.thrust.y > ThrustMax) {
      physics.thrust.y = ThrustMax;
    }
    physics.Move();

    // Update boost location
    boost.location.y = physics.location.y;
    super_boost_left.location.y = physics.location.y - 1;
    super_boost_right.location.y = physics.location.y - 1;

    if (super_boost) {
      boost.boostFactor = 1;
      super_boost_left.boostFactor = 1;
      super_boost_right.boostFactor = 1;
    } else {
      boost.boostFactor = physics.thrust.y / ThrustMax;
      super_boost_left.boostFactor = 0;
      super_boost_right.boostFactor = 0;
    }
  }

  void Draw(display::Display* display) {
    // Draw the rocket boost first (layer behind the rocket)
    boost.Draw(display);
    super_boost_left.Draw(display);
    super_boost_right.Draw(display);

    // Draw the rocket ship
    for (size_t i = max(ceil(physics.location.y), 0);
         i < min(physics.location.y + height, display->size.height); ++i) {
      display->Pixel(physics.location.x, i) = color;
    }

    // dither rocket nose
    display->DitherPixelY(physics.location.x, physics.location.y + height - 1,
                          color);

    // dither rocket tail
    display->DitherPixelY(physics.location.x, physics.location.y, color);
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
