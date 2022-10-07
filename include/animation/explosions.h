#pragma once

#include "animation/animation.h"  // for Animation
#include "animation/explosion.h"  // for Explosion

namespace kss {
namespace animation {

// We are an animation, which is also a vector of explosions
class Explosions : public Animation, public std::vector<Explosion> {
 public:
  void Move() override {
    // Move & Remove dead explosives
    for (auto it = begin(); it < end();) {
      it->Move();
      if (it->IsBurnedOut()) {
        it = erase(it);
      } else {
        ++it;
      }
    }
  }

  void Draw(display::Display* display) override {
    for (auto& explody : *this) {
      explody.Draw(display);
    }
  }
};

}  // namespace animation
}  // namespace kss
