#pragma once
#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "engines/noise.h"        // for NoiseGenerator

namespace kss {
namespace animation {

class NoiseAnimation : public Animation {
 private:
  int brightness = 255;
  engines::NoiseGenerator noise_generator;

 public:
  NoiseAnimation(int width, int height)
      : Animation(), noise_generator(width, height) {}

  void setBrightness(int bright) { brightness = bright; }

  void draw(display::Display* display) {
    static uint8_t ihue = 0;
    noise_generator.fillnoise8();
    for (int i = 0; i < display->numStrips; i++) {
      for (int j = 0; j < display->lengthStrips; j++) {
        // We use the value at the (i,j) coordinate in the noise
        // array for our brightness, and the flipped value from (j,i)
        // for our pixel's hue.
        // leds[i][j] = CHSV(noise_generator.data[j][i], 255,
        // noise_generator.data[i][j]);
        display->Pixel(i, j) = CHSV(ihue + (noise_generator.data[i][j] >> 2),
                                     brightness, noise_generator.data[i][j]);
        // You can also explore other ways to constrain the hue used, like below
        // leds[XY(i,j)] = CHSV(ihue + (noise_generator.data[j][i]>>2), 255,
        // noise_generator.data[i][j]);
      }
    }

    ihue++;
  }
};

}  // namespace animation
}  // namespace kss
