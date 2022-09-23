#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "engines/noise.h"        // for NoiseGenerator

namespace kss {
namespace animation {

class NoiseAnimation : public Animation {
  engines::NoiseGenerator noise_generator;
  const math::Dimension size;
  const math::Dimension location;

  bool use_rainbow_hue;
  uint8_t hue;

 public:
  uint8_t brightness{255};

  NoiseAnimation(math::Dimension size)
      : Animation(),
        noise_generator{size},
        size{size},
        location{0, 0},
        use_rainbow_hue{true} {}

  NoiseAnimation(uint8_t hue, float speed, math::Dimension size,
                 math::Dimension location = {0, 0})
      : Animation(),
        noise_generator{size, speed},
        size{size},
        location{location},
        use_rainbow_hue{false},
        hue{hue} {}

  void setBrightness(uint8_t bright) { brightness = bright; }

  void draw(display::Display* display) override {
    static uint8_t ihue = 0;
    noise_generator.fillnoise8();

    for (size_t i = 0; i < size.x; i++) {
      for (size_t j = 0; j < size.y; j++) {
        if (use_rainbow_hue) {
          // We use the value at the (i,j) coordinate in the noise
          // array for our brightness, and the flipped value from (j,i)
          // for our pixel's hue.
          // leds[i][j] = CHSV(noise_generator.data[j][i], 255,
          // noise_generator.data[i][j]);
          display->Pixel(location.x + i, location.y + j) =
              CHSV(ihue + (noise_generator.data[i][j] >> 2), brightness,
                   noise_generator.data[i][j]);
          // You can also explore other ways to constrain the hue used, like
          // below leds[XY(i,j)] = CHSV(ihue + (noise_generator.data[j][i]>>2),
          // 255, noise_generator.data[i][j]);
        } else {
          display->Pixel(location.x + i, location.y + j) =
              CHSV(hue, 255 - brightness, 128 - noise_generator.data[i][j] / 2);
        }
      }
    }

    ihue++;
  }
};

}  // namespace animation
}  // namespace kss
