#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for display::Display
#include "engines/noise.h"        // for NoiseGenerator

namespace kss {
namespace games {
namespace rocket {

class RocketBoost : public animation::Animation {
 private:
  engines::NoiseGenerator noise_engine_;

 public:
  int loc;
  int height;
  float boostFactor;

  RocketBoost(int heightMax) : Animation(), height{heightMax}, noise_engine_{1, heightMax, 100} {
    loc = 0;
    boostFactor = 0;
  }

  // override rainbow draw function
  void draw(display::Display* display) {
    noise_engine_.fillnoise8();

    // normalize boostFactor to 0-1 range
    if (boostFactor > 1) {
      boostFactor = 1;
    }

    // Draw as much boost as we needs
    int boostHeight = boostFactor * height;

    // At least keep it to 1 pixel minimum when we're actually boosting
    if (boostFactor > 0 && boostHeight < 1) {
      boostHeight = 1;
    }

    int middleStrip = display->numStrips / 2;
    for (int i = max(loc - boostHeight, 0); i < min(loc, display->lengthStrips);
         i++) {
      display->strips[middleStrip][i].setRGB(
          255, noise_engine_.data[0][loc - i], 0);
    }
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
