#pragma once

#include <vector>

#include "animation/animation.h"   // for Animation
#include "audio/sound_effect.h"    // for SoundEffect
#include "display/display.h"       // for Display
#include "engines/physics_info.h"  // for PhysicsInfo
#include "engines/random.h"        // for random::*
#include "serial/debug.h"          // for debug::*

namespace kss {
namespace animation {

class Explosion : Animation {
  enum Phase { Exploding, Fading, Done };

  audio::SoundEffect* explode_sound;

 public:
  uint32_t birthTimeMillis{0};

  uint32_t saturationPhaseMillis = 1000;  // 1 sec sat phase
  uint32_t brightnessPhaseMillis = 1500;  // then 1.5 sec brightness phase

 private:
  Phase GetPhase(uint32_t time_alive) const {
    if (time_alive < saturationPhaseMillis) {
      return Phase::Exploding;
    }
    time_alive -= saturationPhaseMillis;
    if (time_alive < brightnessPhaseMillis) {
      return Phase::Fading;
    }
    return Phase::Done;
  }

 public:
  std::vector<engines::PhysicsInfo> shrapnel;

  int explosionMagnitude = 20;

  // colors (HSV)
  uint8_t Hue;
  uint8_t SaturationFinal = 255;

  Explosion(size_t shrapnelCount, audio::SoundEffect* explode_sound = NULL)
      : Animation(),
        explode_sound{explode_sound},
        shrapnel{shrapnelCount},
        Hue{engines::random::Int8()} {
    SetFriction(4, 1);
  }

  void SetFriction(float xfriction, float friction) {
    for (size_t i = 0; i < shrapnel.size(); i++) {
      shrapnel[i].Friction = friction;
      shrapnel[i].xFriction = xfriction;
    }
  }

  void SetGravity(int gravity) {
    for (size_t i = 0; i < shrapnel.size(); i++) {
      shrapnel[i].Gravity = gravity;
    }
  }

  void ExplodeAt(int stripIndex, int location) {
    birthTimeMillis = millis();

    // Play the sound effect
    if (explode_sound != NULL) {
      explode_sound->Play();
    }

    for (size_t i = 0; i < shrapnel.size(); i++) {
      shrapnel[i].Reset();
      shrapnel[i].Location = location;
      shrapnel[i].xLocation = stripIndex;
      shrapnel[i].RandomizeVelocityVector(explosionMagnitude);
    }
  }

  virtual void Move() override {
    if (IsBurnedOut() == false) {
      for (size_t i = 0; i < shrapnel.size(); i++) {
        shrapnel[i].Move();
      }
    }
  }

  uint32_t TimeAliveMillis() const { return millis() - birthTimeMillis; }

  bool IsBurnedOut() const {
    return GetPhase(TimeAliveMillis()) == Phase::Done;
  }

  void draw(display::Display* display) {
    if (IsBurnedOut())  // don't drawing after the explosion burns out
    {
      return;
    }

    const auto timeAliveMillis = TimeAliveMillis();
    debug::println((String) "==== draw(), timeAlizeMillis = " +
                   timeAliveMillis + ", sat-phase=" + saturationPhaseMillis +
                   ", bright-phase=" + brightnessPhaseMillis);

    const auto phase = GetPhase(timeAliveMillis);

    // Saturate Color while we're in the saturation phase
    int saturation;
    if (phase == Phase::Exploding) {
      saturation = (float)SaturationFinal * (float)timeAliveMillis /
                   (float)saturationPhaseMillis;
    } else {
      saturation = SaturationFinal;
    }

    // Then fade to Black for the brightness phase
    int brightness;
    if (phase == Phase::Exploding) {
      brightness = 255;
      debug::print((String) "SATURATION phase");
    } else if (phase == Phase::Fading) {
      brightness =
          255 *
          (1.0 - (float)(timeAliveMillis - saturationPhaseMillis) /
                     (float)(brightnessPhaseMillis - saturationPhaseMillis));

      debug::print((String) "BRIGHTNESS phase");
    } else {
      brightness = 0;
      debug::print((String) "END phase");
    }
    debug::println((String) " saturation=" + saturation +
                   ", brightness=" + brightness);

    for (size_t i = 0; i < shrapnel.size(); i++) {
      int loc = (int)shrapnel[i].Location;
      int xLoc = (int)shrapnel[i].xLocation;
      if (loc >= 0 && loc < display->strip_length && xLoc >= 0 &&
          xLoc < display->strip_count) {
        CRGB clr;
        clr.setHSV(Hue, saturation, brightness);
        float blend = (float)brightness / (float)255;
        display->DitherPixel(xLoc, shrapnel[i].Location, &clr, blend);
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
