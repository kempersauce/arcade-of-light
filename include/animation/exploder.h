#pragma once

#include "animation/animation.h"  // for Animation
#include "animation/explosion.h"  // for Explosion
#include "math/vector2d.h"        // for Dimension

namespace kss {
namespace animation {

class Exploder : public Animation {
  const Explosion prototype;
  const uint32_t interval;

  std::vector<Explosion*> explosives;

 public:
  math::Dimension location;
  Exploder(const Explosion& prototype, const math::Dimension& location,
           const uint32_t interval = 50)
      : Animation(),
        prototype{prototype},
        interval{interval},
        location{location} {}

  ~Exploder() { Clear(); }

  virtual void Move() override {
    Debug("Start");
    // Fire explosives when it's time
    if (ShouldCreateAnother()) {
      Debug("Creating explosion...");
      explosives.push_back(new Explosion{prototype});
      explosives.back()->ExplodeAt(location.x, location.y);
    }

    // Move each explosive, they're all active
    for (auto explosive : explosives) {
      Debug("Moving explosion...");
      explosive->Move();
    }

    // Remove dead explosives
    for (auto it = explosives.begin(); it < explosives.end();) {
      if ((*it)->IsBurnedOut()) {
        Debug("Deleting explosion...");
        delete *it;
        it = explosives.erase(it);
      } else {
        ++it;
      }
    }
  }

  virtual void draw(display::Display* display) override {
    for (auto explosive : explosives) {
      explosive->draw(display);
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
    const uint32_t now = millis();
    if (now >= next_create) {
      next_create += interval;
      return true;
    }
    return false;
  }
};

}  // namespace animation
}  // namespace kss
