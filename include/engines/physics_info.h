#pragma once

#include "math/random.h"    // for random::*
#include "math/vector2d.h"  // for Vector2D
#include "time/now.h"       // for Now

namespace kss {
namespace engines {

class PhysicsInfo {
  // Track physics based on time not frames
  uint32_t last_move_time;

 public:
  // Dynamic values
  math::Vector2D<float> location;
  math::Vector2D<float> velocity;
  math::Vector2D<float> thrust;
  math::Vector2D<float> gravity;

  // technically not a vector, but we set different values for x & y
  // coefficients since we dont have uniform directional dimension
  math::Vector2D<float> friction;

  // Edge detection
  bool respect_edges;  // Whether or not to perform edge detection at all
  bool HasHitEdge;  // updated every round to determine if the edge was hit this
                    // round
  bool HasExploded;  // set to true when exploded, only reset on Reset()

  // Configurable values - these default to values that make them not used
  // unless set
  int LocationMax = UINT16_MAX;  // default to this to have no ceiling ... 0 is
                                 // still hardcoded on the bottom
  float ThrustMax = 200;         // ???
  int Mass = 1;                  // default to 1 so thrust = acceleration

  float BounceFactor = 1.0;  // default to 1 for no bounce
  int ExplodeVelocity = 0;   // default to 0 to explode on contact

  PhysicsInfo() { Reset(); }

  void RandomizeVelocityVector(float maxMagnitude) {
    velocity = math::Vector2D<float>::RandomVector(maxMagnitude);
  }

  void Reset() {
    // Re-init physical vectors
    velocity = math::Vector2D<float>();
    location = math::Vector2D<float>();
    thrust = math::Vector2D<float>();

    // Reset collision detection
    respect_edges = true;
    HasHitEdge = false;
    HasExploded = false;

    // Update time tracking
    last_move_time = time::Now();
  }

  void Move() {
    if (thrust.y > ThrustMax) {
      thrust.y = ThrustMax;
    }

    const auto now = time::Now();
    const float timeDiff = (float)(now - last_move_time) / 1000.0f;

    last_move_time = now;

    // Equations
    const auto acceleration = (thrust / Mass)           // force on the object
                              - gravity                 // subtract for gravity
                              - (velocity * friction);  // subtract for friction

    // Adjust velocity
    velocity += acceleration * timeDiff;

    // TODO we used to compute friction based on the new velocity, not the old
    // one
    // velocity -= velocity * friction * timeDiff;

    // Adjust location
    location += velocity * timeDiff;

    HasHitEdge = (location.y < 0 || location.y >= LocationMax);

    if (respect_edges) {
      // rocket has slammed into ceiling or floor
      if (location.y >= LocationMax) {
        location.y = LocationMax - 1;
      } else if (location.y < 0) {
        location.y = 0;
      }

      if (HasHitEdge) {
        // and exploded
        if (abs(velocity.y) >= ExplodeVelocity) {
          HasExploded = true;
        }

        // and bounced off ceiling/floor
        else {
          velocity *= BounceFactor;
        }
      }
    }
  }
};

}  // namespace engines
}  // namespace kss
