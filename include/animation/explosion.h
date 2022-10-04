#pragma once

#include <vector>

#include "animation/animation.h"   // for Animation
#include "audio/sound_effect.h"    // for SoundEffect
#include "display/display.h"       // for Display
#include "engines/physics_info.h"  // for PhysicsInfo
#include "math/random.h"           // for random::*
#include "math/vector2d.h"         // for Vector2D
#include "serial/debug.h"          // for Debug
#include "time/now.h"              // for Now

namespace kss {
namespace animation {

class Explosion : Animation {
  enum Phase { NotStarted, Exploding, Fading, Done };

  size_t shrapnel_count{50};

  uint32_t saturation_phase_ms{1000};  // 1 sec sat phase
  uint32_t brightness_phase_ms{1500};  // then 1.5 sec brightness phase

  float magnitude{20.0f};
  math::Vector2D<float> friction{4, 1};
  math::Vector2D<float> gravity{0, 15};

  uint8_t saturation_final{255};
  uint8_t hue{0};

  audio::SoundEffect* explode_sound{NULL};

  uint32_t birthTimeMillis{0};

  uint32_t TimeAliveMillis() const { return time::Now() - birthTimeMillis; }

  Phase GetPhase() const {
    if (birthTimeMillis == 0) {
      return Phase::NotStarted;
    }

    const auto time_alive = TimeAliveMillis();

    if (time_alive < saturation_phase_ms) {
      return Phase::Exploding;
    }

    if (time_alive < saturation_phase_ms + brightness_phase_ms) {
      return Phase::Fading;
    }

    return Phase::Done;
  }

 public:
  std::vector<engines::PhysicsInfo> shrapnel;

  Explosion(size_t shrapnel_count, uint32_t saturation_phase_ms,
            uint32_t brightness_phase_ms, float magnitude, float friction_x,
            float friction_y, float gravity, uint8_t saturation_final,
            uint8_t hue, audio::SoundEffect* explode_sound = NULL)
      : Animation(),
        shrapnel{shrapnel_count},
        saturation_phase_ms{saturation_phase_ms},
        brightness_phase_ms{brightness_phase_ms},
        magnitude{magnitude},
        friction{friction_x, friction_y},
        gravity{0, gravity},
        saturation_final{saturation_final},
        hue{hue},
        explode_sound{explode_sound} {}

  void SetHue(uint8_t value) { hue = value; }

  void SetGravity(int grav) { gravity.y = grav; }

  void ExplodeAt(int stripIndex, int location,
                 math::Vector2D<float> additional = {0, 0}) {
    birthTimeMillis = time::Now();

    // Play the sound effect
    if (explode_sound != NULL) {
      explode_sound->Play();
    }

    for (auto& shrap : shrapnel) {
      shrap.Reset();
      shrap.friction = friction;
      shrap.gravity = gravity;
      shrap.location = math::Vector2D<float>{stripIndex, location};
      shrap.velocity =
          math::Vector2D<float>::RandomVector(magnitude) + additional;
    }
  }

  void Move() override {
    const auto phase = GetPhase();

    // don't Draw before exploding or after the explosion burns out
    if (phase == Phase::Done || phase == Phase::NotStarted) {
      return;
    }

    for (auto& shrap : shrapnel) {
      shrap.Move();
    }
  }

  bool IsBurnedOut() const { return GetPhase() == Phase::Done; }

  void Draw(display::Display* display) {
    const auto timeAliveMillis = TimeAliveMillis();
    // Debug("==== Draw(), timeAliveMillis = " +
    //                timeAliveMillis + ", sat-phase=" + saturation_phase_ms +
    //                ", bright-phase=" + brightness_phase_ms);

    const auto phase = GetPhase();

    // don't Draw before exploding or after the explosion burns out
    if (phase == Phase::Done || phase == Phase::NotStarted) {
      return;
    }

    // Saturate Color while we're in the saturation phase
    uint8_t saturation;
    if (phase == Phase::Exploding) {
      saturation = (float)saturation_final * (float)timeAliveMillis /
                   (float)saturation_phase_ms;
    } else {
      saturation = saturation_final;
    }

    // Then fade to Black for the brightness phase
    uint8_t brightness;
    if (phase == Phase::Exploding) {
      brightness = 255;
      // Debug("SATURATION phase sat=" + saturation + ", bright=" + brightness);
    } else if (phase == Phase::Fading) {
      brightness = 255 * (1.0 - (float)(timeAliveMillis - saturation_phase_ms) /
                                    (float)brightness_phase_ms);

      // Debug("BRIGHTNESS phase sat=" + saturation + ", bright=" + brightness);
    } else {
      brightness = 0;
      // Debug("END phase sat=" + saturation + ", bright=" + brightness);
    }

    for (const auto& shrap : shrapnel) {
      const auto& loc = shrap.location;
      if (loc.y >= 0 && loc.y < display->size.y && loc.x >= 0 &&
          loc.x < display->size.x) {
        CRGB color = CHSV(hue, saturation, brightness);
        const float blend = (float)brightness / 255.0f;
        display->DitherPixelY(loc.x, loc.y, color, blend);
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
