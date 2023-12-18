#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "engines/noise.h"        // for NoiseGenerator
#include "math/vector2d.h"        // for Vector2D

namespace kss {
namespace games {
namespace rocket {

class RocketBoost : public animation::Animation {
  engines::NoiseGenerator noise_generator;
  const float opacity;

 public:
  math::Vector2D<float> location;
  size_t height;
  float boostFactor;

  RocketBoost(size_t heightMax, size_t x, float opacity = 1)
      : Animation(),
        noise_generator{{1, heightMax}, 100},
        opacity{opacity},
        height{heightMax} {
    boostFactor = 0;
    location.x = x;
  }

  void Draw(display::Display* display) {
    noise_generator.fillnoise8();

    // normalize boostFactor to 0-1 range
    if (boostFactor > 1) {
      boostFactor = 1;
    }

    // Draw as much boost as we needs
    float boostHeight = boostFactor * height;

    // At least keep it to 1 pixel minimum when we're actually boosting
    if (boostFactor > 0 && boostHeight < 1) {
      boostHeight = 1;
    }

    // Break out if there's no boost to draw
    if (boostHeight <= 0) {
      return;
    }

    const float y_start = max(location.y - boostHeight, 0);
    for (size_t i = ceil(location.y - boostHeight); i < location.y; ++i) {
      const CRGB color{255, noise_generator.Data(0, location.y - i), 0};
      display->BlendPixel(location.x, i, color, opacity);
    }

    // Dither up towards the rocket
    display->DitherPixelY(location.x, location.y,
                          CRGB(255, noise_generator.Data(0, 0), 0));

    // Dither end of tail
    display->BlendPixel(
        location.x, y_start,
        CRGB(255, noise_generator.Data(0, ceil(boostHeight)), 0),
        opacity * (1 - fmod(y_start, 1)));
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
