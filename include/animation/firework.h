#pragma once

#include "animation/animation.h"  // for Animation
#include "animation/explosion.h"  // for Explosion
#include "audio/sound_effect.h"   // for SoundEffect
#include "display/display.h"      // for Display
#include "engines/random.h"       // for random::*

namespace kss {
namespace animation {

// TODO move this to animations, this is a generic animation
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
  Firework(int strip_length, int strip_count, audio::SoundEffect* launch_sound,
           audio::SoundEffect* explode_sound)
      : Animation(),
        launch_sound{launch_sound},
        explosion(50, explode_sound),
        strip_length{strip_length},
        strip_count{strip_count} {
    Reset();
  }

  void Reset() {
    isPlaying = false;
    physics.Reset();
    physics.LocationMax = engines::random::Int16(
        strip_length / 3, strip_length - 20);  // height the firework explodes
    physics.Velocity =
        engines::random::Int8(35, 75);  // how fast do we get there

    physics.xLocation = engines::random::Int8(
        strip_count);  // select which strip this should be on

    hue = engines::random::Int8();
  }

  void Move() {
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
        explosion.Hue = engines::random::Int8();
        explosion.ExplodeAt(physics.xLocation, physics.Location);
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
      int Saturation = min(255 * (physics.Location / physics.LocationMax), 255);
      CRGB color;
      color.setHSV(hue, Saturation, 255);
      display->DitherPixel((int)physics.xLocation, (int)physics.Location,
                           &color);
    }
  }
};

}  // namespace animation
}  // namespace kss
