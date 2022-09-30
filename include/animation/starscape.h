#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "engines/noise.h"        // for NoiseGenerator
#include "math/vector2d.h"        // for Dimension

namespace kss {
namespace animation {

class Starscape : public Animation {
  const uint8_t brightness_threshold;

 public:
  engines::NoiseGenerator noise_generator;

  Starscape(const math::Dimension& size,
            const uint8_t brightness_threshold = 140)
      : Animation(),
        brightness_threshold{brightness_threshold},
        noise_generator{size, 7} {}

  void Draw(display::Display* display) {
    noise_generator.fillnoise8();

    for (size_t x = 0; x < display->size.x; ++x) {
      for (size_t y = 0; y < display->size.y; ++y) {
        uint8_t brightness = noise_generator.data[x][y];
        if (brightness > brightness_threshold) {
          // Draw the star, it's past the threshold

          // stretch the brightness so it goes from 0-100 for CSV
          uint8_t value = 255 * (brightness - brightness_threshold) /
                          (255 - brightness_threshold);

          // Draw onto the blackness of space
          display->Pixel(x, y) =
              CHSV(46, value, value);  // Amber is 46, 100, 100 - we scale from
                                       // black up to amber here
        } else {
          // Draw the blackness of space
          display->Pixel(x, y) = CRGB(0, 0, 0);
        }
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
