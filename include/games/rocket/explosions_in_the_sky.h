#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "games/rocket/audio.h"   // for RocketAudio
#include "time/now.h"             // for Now

namespace kss {
namespace games {
namespace rocket {

class ExplosionsInTheSky : public animation::Animation {
  static constexpr uint32_t animationLengthMillis{7000};
  const CRGB color;
  uint32_t timeStart = 0;

 public:
  ExplosionsInTheSky() : Animation(), color{CRGB::Red} {}

  void startAnimation(RocketAudio& audio) { timeStart = time::Now(); }

  bool isPlaying() { return timeStart != 0; }

  void Draw(display::Display* display) {
    uint32_t timeDiff = time::Now() - timeStart;

    // Draw explosion accross all strips
    for (size_t j = 0; j < display->size.x; j++) {
      // sets the top 2/3 pixels in a fade from red to black
      int explosionHeight = display->size.y * 2 / 3;
      for (size_t i = display->size.y - explosionHeight; i < display->size.y;
           i++) {
        float blendStrength = (float)timeDiff / (float)animationLengthMillis;
        float positionFactor =
            (float)(i - (display->size.y - explosionHeight)) /
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
