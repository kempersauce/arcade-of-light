#pragma once

#include "animation/animation.h"  // for Animation
#include "animation/explosion.h"  // for Explosion
#include "audio/sound_effect.h"   // for SoundEffect
#include "display/display.h"      // for Display
#include "math/random.h"          // for random::*

namespace kss {
namespace animation {

// A single firework
class Firework : public Animation {
  audio::SoundEffect* launch_sound;

  // Used to randomly select the strip and explosion height when resetting the
  // firework
  const size_t strip_length;
  const size_t strip_count;

 public:
  // Physics for the fireworks "rocket"
  engines::PhysicsInfo physics;

  // Fireworks explosion
  Explosion explosion;

  // color for the firework rocket
  uint8_t hue;

  bool isPlaying;

  /**
   * Firework Constructor
   * @param strip_length - location on LED strip
   * */
  Firework(size_t strip_length, size_t strip_count, float explosion_gravity,
           audio::SoundEffect* launch_sound = NULL,
           audio::SoundEffect* explode_sound = NULL)
      : Animation(),
        launch_sound{launch_sound},
        strip_length{strip_length},
        strip_count{strip_count},
        explosion{100,
                  1000,
                  2000,
                  30,
                  4,
                  2,
                  explosion_gravity,
                  255,
                  math::random::Int8(),
                  explode_sound} {
    Reset();
  }

  void Reset() {
    isPlaying = false;
    physics.Reset();
    physics.LocationMax = math::random::Int16(
        strip_length / 3, strip_length - 20);  // height the firework explodes
    physics.velocity.y =
        math::random::Int8(35, 75);  // how fast do we get there

    physics.location.x = math::random::Int8(
        strip_count);  // select which strip this should be on

    hue = math::random::Int8();
  }

  virtual void Move() override {
    if (!isPlaying) {
      if (launch_sound != NULL) {
        launch_sound->Play();
      }
      isPlaying = true;
    }
    bool wasExploded = physics.HasExploded;  // edge was set with LocationMax to
                                             // denote the explode height

    physics.Move();

    // Explode when we get to the designated height
    if (physics.HasExploded) {
      if (wasExploded == false) {
        explosion.ExplodeAt(physics.location.x, physics.location.y,
                            physics.velocity / 4);
      }

      explosion.Move();

      if (explosion.IsBurnedOut()) {
        isPlaying = false;
      }
    }
  }

  void draw(display::Display* display) {
    if (physics.HasExploded) {
      explosion.draw(display);
    } else {
      int Saturation =
          min(255 * (physics.location.y / physics.LocationMax), 255);
      CRGB color;
      color.setHSV(hue, Saturation, 255);
      display->DitherPixel((int)physics.location.x, (int)physics.location.y,
                           &color);
    }
  }
};

}  // namespace animation
}  // namespace kss
