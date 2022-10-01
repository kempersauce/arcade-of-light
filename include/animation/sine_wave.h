#pragma once

#include <math.h>  // for fmod

#include "animation/animation.h"  // for Animation
#include "serial/debug.h"         // for Debug

namespace kss {
namespace animation {

class SineWave : public Animation {
  float y_offset{0};

 public:
  CRGB color;

  // sine wavelength in pixels
  float wavelength{100};
  float amplitude{2};

  // pixels per millisecond
  float speed{.25};

  SineWave(CRGB color) : Animation(), color{color} {}

  void Move() override {
    y_offset = fmod(y_offset + time::ElapsedMillis() * speed, wavelength);
  }

  void DrawFloat(display::Display* display, float x, size_t y) {
    display->DitherPixelX(x, y, &color);
  }

  void Draw(display::Display* display) override {
    for (size_t y = 0; y < display->size.y; ++y) {
      //   Debug_var(y);
      const uint8_t theta = 255.0f * ((float)y + y_offset) / wavelength;
      //   Debug_var(theta);
      // xsine goes -1 -> 1
      float sine = ((float)sin8(theta) - 128.0f) / 128.0f;
      //   Debug_var(sine);
      float x = ((float)(display->size.x - 1) / 2) + amplitude * sine;
      //   Debug_var(x);
      // Debug("y="+y+", y_offset="+y_offset+", x=")
      display->DitherPixelX(x, y, &color);
    }
    // while(true){} // for testing vars
  }
};

}  // namespace animation
}  // namespace kss
