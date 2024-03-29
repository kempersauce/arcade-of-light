#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "engines/noise.h"        // for NoiseGenerator
#include "math/vector2d.h"        // for Dimension

namespace kss {
namespace animation {

class Starscape : public Animation {
  const uint8_t brightness_threshold;
  engines::NoiseGenerator internal;

 public:
  uint8_t hue{46};  // nice amber for stars
  engines::NoiseGenerator* noise_generator;

  Starscape(math::Dimension size, const uint8_t brightness_threshold = 140)
      : Animation(),
        brightness_threshold{brightness_threshold},
        internal{size, 7},
        noise_generator{&internal} {}

  Starscape(engines::NoiseGenerator* noise_generator,
            const uint8_t brightness_threshold = 140)
      : Animation(),
        brightness_threshold{brightness_threshold},
        noise_generator{noise_generator} {}

  CRGB GetPixel(const size_t x, const size_t y) const {
    const uint8_t brightness = noise_generator->Data(x, y);
    if (brightness > brightness_threshold) {
      // Draw the star, it's past the threshold

      // stretch the brightness so it goes from 0-100 for CSV
      uint8_t value = 255 * (brightness - brightness_threshold) /
                      (255 - brightness_threshold);

      // Draw onto the blackness of space
      return CHSV(hue, value, value);
    } else {
      // Draw the blackness of space
      return CRGB::Black;
    }
  }

  void Move() override { noise_generator->fillnoise8(); }

  void Draw(display::Display* display) override {
    for (size_t x = 0; x < display->size.x; ++x) {
      for (size_t y = 0; y < display->size.y; ++y) {
        display->Pixel(x, y) = GetPixel(x, y);
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
