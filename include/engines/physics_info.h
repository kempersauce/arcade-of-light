#pragma once

#include "engines/physics_basic.h"  // for PhysicsBasic
#include "math/random.h"            // for random::*
#include "math/vector2d.h"          // for Vector2D
#include "time/now.h"               // for Now

namespace kss {
namespace engines {

class PhysicsInfo : public PhysicsBasic {
 public:
  // Edge detection
  bool respect_edges{true};  // Whether or not to perform edge detection at all

  // updated every round to determine if the edge was hit this round
  bool HasHitEdge{false};

  // set to true when exploded, only reset on Reset()
  bool HasExploded{false};

  // Configurable values
  // these default to values that make them not used unless set
  uint16_t LocationMax = UINT16_MAX;  // default to this to have no ceiling ...
                                      // 0 is still hardcoded on the bottom

  float BounceFactor = 1.0;  // default to 1 for no bounce
  int ExplodeVelocity = 0;   // default to 0 to explode on contact

  PhysicsInfo() : PhysicsBasic() { Reset(); }

  void Reset() {
    // Re-init physical vectors
    PhysicsBasic::Reset();

    // Reset collision detection
    respect_edges = true;
    HasHitEdge = false;
    HasExploded = false;
  }

  void Move() {
    // Do basic physics motion
    PhysicsBasic::Move();

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
