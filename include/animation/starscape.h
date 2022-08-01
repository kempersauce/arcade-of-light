#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "engines/noise.h"        // for NoiseGenerator

namespace kss {
namespace animation {

class Starscape : public Animation {
  const int brightnessThreshold;

 public:
  engines::NoiseGenerator noise_generator;

  Starscape(int width, int height, int brightnessThreshold)
      : Animation(),
        brightnessThreshold{brightnessThreshold},
        noise_generator(width, height, 7) {}

  void draw(display::Display* display) {
    noise_generator.fillnoise8();

    for (int i = 0; i < display->numStrips; i++) {
      for (int j = 0; j < display->lengthStrips; j++) {
        int brightness = noise_generator.data[i][j];
        if (brightness > brightnessThreshold) {
          // Draw the star, it's past the threshold

          // stretch the brightness so it goes from 0-100 for CSV
          int value = 255 * (brightness - brightnessThreshold) /
                      (255 - brightnessThreshold);

          // draw onto the blackness of space
          display->Pixel(i, j) =
              CHSV(46, value, value);  // Amber is 46, 100, 100 - we scale from
                                       // black up to amber here
        } else {
          // Draw the blackness of space
          display->Pixel(i, j) = CRGB(0, 0, 0);
        }
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
