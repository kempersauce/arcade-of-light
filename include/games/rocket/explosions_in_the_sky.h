#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "games/rocket/audio.h"   // for RocketAudio

namespace kss {
namespace games {
namespace rocket {

class ExplosionsInTheSky : public animation::Animation {
  long timeStart = 0;
  long animationLengthMillis = 7000;
  CRGB* color;

 public:
  ExplosionsInTheSky() : Animation(), color{new CRGB(255, 0, 0)} {}

  void startAnimation(RocketAudio& audio) {
    timeStart = millis();
    // audio.playExplosion();
  }

  bool isPlaying() { return timeStart != 0; }

  void draw(display::Display* display) {
    long timeDiff = millis() - timeStart;

    // Draw explosion accross all strips
    for (size_t j = 0; j < display->strip_count; j++) {
      // sets the top 2/3 pixels in a fade from red to black
      int explosionHeight = display->strip_length * 2 / 3;
      for (size_t i = display->strip_length - explosionHeight;
           i < display->strip_length; i++) {
        float blendStrength = (float)timeDiff / (float)animationLengthMillis;
        float positionFactor =
            (float)(i - (display->strip_length - explosionHeight)) /
            (float)explosionHeight;
        blendStrength *= positionFactor;
        display->BlendPixel(j, i, color, blendStrength);
      }
    }

    if (timeDiff > animationLengthMillis) {
      timeStart = 0;
    }
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
