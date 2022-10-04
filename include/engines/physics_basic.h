#pragma once

#include "math/random.h"    // for random::*
#include "math/vector2d.h"  // for Vector2D
#include "time/now.h"       // for Now

namespace kss {
namespace engines {

class PhysicsBasic {
 public:
  // Dynamic values
  math::Vector2D<float> location;
  math::Vector2D<float> velocity;
  math::Vector2D<float> thrust;
  math::Vector2D<float> gravity;

  // technically not a vector, but we set different values for x & y
  // coefficients since we dont have uniform directional dimension
  math::Vector2D<float> friction;

  PhysicsBasic() {}
  virtual ~PhysicsBasic() = default;

  void RandomizeVelocityVector(float maxMagnitude) {
    velocity = math::Vector2D<float>::RandomVector(maxMagnitude);
  }

  void Reset() {
    // Re-init physical vectors
    velocity = math::Vector2D<float>();
    location = math::Vector2D<float>();
    thrust = math::Vector2D<float>();
  }

  void Move() {
    const float timeDiff = (float)(time::LoopElapsedMillis()) / 1000.0f;

    // Equations
    const auto acceleration = thrust                    // force on the object
                              - gravity                 // subtract for gravity
                              - (velocity * friction);  // subtract for friction

    // Adjust velocity
    velocity += acceleration * timeDiff;

    // Adjust location
    location += velocity * timeDiff;
  }
};

}  // namespace engines
}  // namespace kss
