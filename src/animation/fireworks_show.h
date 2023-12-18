#pragma once

#include <vector>  // for std::vector

#include "animation/animation.h"  // for Animation
#include "animation/firework.h"   // for Firework
#include "audio/sound_effect.h"   // for SoundEffect
#include "display/display.h"      // for Display
#include "math/random.h"          // for random::*
#include "time/now.h"             // for Now

namespace kss {
namespace animation {

namespace _fireworks_show {

constexpr size_t kMaxFireworksCount{0};  // 0 for no-limit
constexpr uint16_t kMinWaitTime{50};
constexpr uint16_t kMaxWaitTime{2000};

}  // namespace _fireworks_show
using namespace _fireworks_show;

class FireworksShow : Animation {
  std::vector<Firework*> fireworks;

  audio::SoundEffect* launch_sound;
  audio::SoundEffect* explode_sound;

  const math::Dimension display_size;

  float gravity;

 public:
  FireworksShow(const math::Dimension& display_size, float gravity,
                audio::SoundEffect* launch_sound = NULL,
                audio::SoundEffect* explode_sound = NULL)
      : Animation(),
        launch_sound{launch_sound},
        explode_sound{explode_sound},
        display_size{display_size},
        gravity{gravity} {}

  ~FireworksShow() { Clear(); }

  void Move() override {
    // Launch 1-3 fireworks when it's time
    if (ShouldCreateAnother()) {
      for (auto count = math::random::Int8_incl(1, 2); count > 0; count--) {
        fireworks.push_back(
            new Firework{display_size, gravity, launch_sound, explode_sound});
      }
    }

    // Move each firework, they're all active
    for (auto firework : fireworks) {
      firework->Move();
    }

    // Remove dead fireworks
    for (auto it = fireworks.begin(); it < fireworks.end();) {
      if (!(*it)->isPlaying) {
        delete *it;
        it = fireworks.erase(it);
      } else {
        ++it;
      }
    }
  }

  void Draw(display::Display* display) override {
    for (auto firework : fireworks) {
      firework->Draw(display);
    }
  }

  void Clear() {
    for (auto firework : fireworks) {
      delete firework;
    }
    fireworks.clear();
  }

  void SetGravity(float grav) { gravity = grav; }

 private:
  uint32_t next_create{0};
  bool ShouldCreateAnother() {
    if (kMaxFireworksCount == 0 || fireworks.size() < kMaxFireworksCount) {
      const uint32_t now = time::Now();
      if (now >= next_create) {
        next_create = now + math::random::Int16(kMinWaitTime, kMaxWaitTime);
        return true;
      }
    }
    return false;
  }
};

}  // namespace animation
}  // namespace kss
