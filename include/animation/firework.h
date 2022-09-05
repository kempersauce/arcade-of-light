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
  const math::Dimension display_size;

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
   * */
  Firework(const math::Dimension& display_size, float explosion_gravity,
           audio::SoundEffect* launch_sound = NULL,
           audio::SoundEffect* explode_sound = NULL)
      : Animation(),
        launch_sound{launch_sound},
		display_size{display_size},
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

  ~Firework(){};

  void Reset() {
    isPlaying = false;
    physics.Reset();
    physics.LocationMax = math::random::Int16(
        display_size.y / 3, display_size.y - 20);  // height the firework explodes
    physics.velocity.y =
        math::random::Int8(35, 75);  // how fast do we get there

    physics.location.x = math::random::Int8(
        display_size.x);  // select which strip this should be on

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
      display->DitherPixel((size_t)physics.location.x, (size_t)physics.location.y,
                           &color);
    }
  }
};

}  // namespace animation
}  // namespace kss
