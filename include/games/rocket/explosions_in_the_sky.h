#pragma once

#include "animation/animation.h"  // for Animation
#include "audio/rocket_audio.h"   // for RocketAudio
#include "display/display.h"      // for kss::display::Display

class ExplosionsInTheSky : public kss::animation::Animation {
  long timeStart = 0;
  long animationLengthMillis = 7000;
  CRGB* color;

 public:
  ExplosionsInTheSky() : Animation(), color{new CRGB(255, 0, 0)} {}

  void startAnimation(kss::audio::RocketAudio& audio) {
    timeStart = millis();
    // audio.playExplosion();
  }

  bool isPlaying() { return timeStart != 0; }

  void draw(kss::display::Display* display) {
    long timeDiff = millis() - timeStart;

    // Draw explosion accross all strips
    for (int j = 0; j < display->numStrips; j++) {
      // sets the top 2/3 pixels in a fade from red to black
      int explosionHeight = display->lengthStrips * 2 / 3;
      for (int i = display->lengthStrips - explosionHeight;
           i < display->lengthStrips; i++) {
        float blendStrength = (float)timeDiff / (float)animationLengthMillis;
        float positionFactor =
            (float)(i - (display->lengthStrips - explosionHeight)) /
            (float)explosionHeight;
        blendStrength *= positionFactor;
        display->blendPixel(j, i, color, blendStrength);
      }
    }

    if (timeDiff > animationLengthMillis) {
      timeStart = 0;
    }
  }
};
