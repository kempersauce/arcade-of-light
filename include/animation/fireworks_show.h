#pragma once

#include <algorithm>  // for remove_if
#include <vector>     // for std::vector

#include "animation/animation.h"  // for Animation
#include "animation/firework.h"   // for Firework
#include "audio/sound_effect.h"   // for SoundEffect
#include "display/display.h"      // for Display
#include "engines/random.h"       // for random::*

namespace kss {
namespace animation {

class FireworksShow : Animation {
  std::vector<Firework*> fireworks;

  audio::SoundEffect* launch_sound;
  audio::SoundEffect* explode_sound;

  const size_t strip_length;
  const size_t strip_count;

 public:
  FireworksShow(size_t strip_length, size_t strip_count,
                audio::SoundEffect* launch_sound = NULL,
                audio::SoundEffect* explode_sound = NULL)
      : Animation(),
        launch_sound{launch_sound},
        explode_sound{explode_sound},
        strip_length{strip_length},
        strip_count{strip_count} {}

  virtual void Move() override {
    // Remove dead fireworks
    for (auto it = fireworks.begin(); it < fireworks.end();) {
      if (!(*it)->isPlaying) {
        delete *it;
        it = fireworks.erase(it);
      } else {
        ++it;
      }
    }

    if (ShouldCreateAnother()) {
      fireworks.push_back(
          new Firework{strip_length, strip_count, launch_sound, explode_sound});
      fireworks.back()->explosion.SetGravity(20);
    }

    // Move each firework that's left
    for (auto firework : fireworks) {
      firework->Move();
    }
  }

  virtual void draw(display::Display* display) override {
    for (auto firework : fireworks) {
      firework->draw(display);
    }
  }

 private:
  uint32_t next_create{0};
  bool ShouldCreateAnother() {
    const uint32_t now = millis();
    if (now >= next_create) {
      next_create = now + engines::random::Int32(100, 2500);
      return true;
    }
    return false;
  }
};

}  // namespace animation
}  // namespace kss
