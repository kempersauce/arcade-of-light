#pragma once

#include <vector>

#include "animation/animation.h"   // for Animation
#include "display/display.h"       // for Display
#include "engines/physics_info.h"  // for PhysicsInfo
#include "engines/random.h"        // for random::*

namespace kss {
namespace animation {

class Explosion : Animation {
 public:
  uint32_t birthTimeMillis;

  std::vector<engines::PhysicsInfo> shrapnel;

  int explosionMagnitude = 100;

  // colors (HSV)
  int Hue;
  int SaturationFinal = 255;
  uint32_t saturationPhaseMillis = 1000;
  uint32_t brightnessPhaseMillis = 1500;

  Explosion(size_t shrapnelCount = 50) : Animation(), shrapnel{shrapnelCount} {
    birthTimeMillis = 0;  // not born yet
    Hue = engines::random::Int8();
    SetFriction(20, 5);
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

    for (size_t i = 0; i < shrapnel.size(); i++) {
      shrapnel[i].Reset();
      shrapnel[i].Location = location;
      shrapnel[i].xLocation = stripIndex;
      shrapnel[i].RandomizeVelocityVector(explosionMagnitude);
    }
  }

  void Move() {
    if (IsBurnedOut() == false) {
      for (size_t i = 0; i < shrapnel.size(); i++) {
        shrapnel[i].Move();
      }
    }
  }

  bool IsBurnedOut() {
    return TimeAliveMillis() >= saturationPhaseMillis + brightnessPhaseMillis;
  }

  uint32_t TimeAliveMillis() { return millis() - birthTimeMillis; }

  void draw(display::Display* display) {
    if (IsBurnedOut())  // don't drawing after the explosion burns out
    {
      return;
    }

    auto timeAliveMillis = TimeAliveMillis();

    // Saturate Color while we're in the saturation phase
    int saturation;
    if (timeAliveMillis < saturationPhaseMillis) {
      saturation = SaturationFinal * (float)timeAliveMillis /
                   (float)saturationPhaseMillis;
    } else {
      saturation = SaturationFinal;
    }

    timeAliveMillis -= saturationPhaseMillis;

    // Then fade to Black for the brightness phase
    int brightness;
    if (timeAliveMillis < 0) {
      brightness = 255;
    } else if (timeAliveMillis < brightnessPhaseMillis) {
      brightness =
          255 * (1.0 - (float)timeAliveMillis / (float)brightnessPhaseMillis);
    } else {
      brightness = 0;
    }

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
