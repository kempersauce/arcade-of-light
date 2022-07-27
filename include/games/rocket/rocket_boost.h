#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "engines/noise.h"        // for NoiseGenerator

namespace kss {
namespace games {
namespace rocket {

class RocketBoost : public animation::Animation {

  engines::NoiseGenerator noise_generator;

 public:
  size_t loc;
  size_t height;
  float boostFactor;

  RocketBoost(size_t heightMax)
      : Animation(), noise_generator{1, heightMax, 100}, height{heightMax} {
    loc = 0;
    boostFactor = 0;
  }

  // override rainbow draw function
  void draw(display::Display* display) {
    noise_generator.fillnoise8();

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
    for (size_t i = max(loc - boostHeight, 0); i < min(loc, display->lengthStrips);
         i++) {
      display->strips[middleStrip][i].setRGB(
          255, noise_generator.data[0][loc - i], 0);
    }
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
