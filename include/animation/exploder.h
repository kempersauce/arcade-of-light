#pragma once

#include "animation/animation.h"  // for Animation
#include "animation/explosion.h"  // for Explosion
#include "math/vector2d.h"        // for Dimension
#include "time/now.h"             // for Now

namespace kss {
namespace animation {

class Exploder : public Animation {
  const Explosion prototype;
  const uint32_t interval;

  std::vector<Explosion*> explosives;

 public:
  math::Dimension location;
  bool should_explode{false};
  Exploder(const Explosion& prototype, math::Dimension location,
           const uint32_t interval = 50)
      : Animation(),
        prototype{prototype},
        interval{interval},
        location{location} {}

  ~Exploder() { Clear(); }

  void Move() override {
    // Debug("Start");
    // Fire explosives when it's time
    if (ShouldCreateAnother()) {
      //   Debug("Creating explosion...");
      explosives.push_back(new Explosion{prototype});
      explosives.back()->ExplodeAt(location.x, location.y);
    }

    // Move each explosive, they're all active
    for (auto explosive : explosives) {
      //   Debug("Moving explosion...");
      explosive->Move();
    }

    // Remove dead explosives
    for (auto it = explosives.begin(); it < explosives.end();) {
      if ((*it)->IsBurnedOut()) {
        // Debug("Deleting explosion...");
        delete *it;
        it = explosives.erase(it);
      } else {
        ++it;
      }
    }
  }

  void Draw(display::Display* display) override {
    for (auto explosive : explosives) {
      explosive->Draw(display);
    }
  }

  void Clear() {
    for (auto explosive : explosives) {
      delete explosive;
    }
    explosives.clear();
  }

 private:
  uint32_t next_create{0};
  bool ShouldCreateAnother() {
    if (should_explode) {
      const uint32_t now = time::Now();
      if (now >= next_create) {
        // This will be problematic, needs to be aligned with actual beat time
        if (next_create == 0) {
          next_create = now;
        }
        next_create += interval;
        return true;
      }
    }
    return false;
  }
};

}  // namespace animation
}  // namespace kss
