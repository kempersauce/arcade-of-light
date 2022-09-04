#pragma once

#include <FastLED.h>  // for millis()

#include "math/random.h"  // for random::*

namespace kss {
namespace engines {

class NoiseGenerator {
  uint32_t lastFrameMillis{0};

  const math::Dimension size;

 public:
  // Notes about speed:
  // 1: almost looks like a painting, moves very slowly
  // 20: (default) a nice starting speed, mixes well with a scale of 100
  // 100: wicked fast!
  const float speed;

  // Scale determines how far apart the pixels in our noise matrix are.  Try
  // changing these values around to see how it affects the motion of the
  // display.  The higher the value of scale, the more "zoomed out" the noise
  // iwll be.  A value of 1 will be so zoomed in, you'll mostly see solid
  // colors.

  // const uint16_t scale = 1; // mostly just solid colors
  // const uint16_t scale = 4011; // very zoomed out and shimmery
  const uint16_t scale = 1024;

  // This is the array that we keep our computed noise values in
  // We make it public so our consumers can directly access our nouse matrix
  uint8_t** data;

  // We're using the x/y dimensions to map to the x/y pixels on the matrix.
  // We'll use the z-axis for "time".  speed determines how fast time moves
  // forward.  Try 1 for a very slow moving effect, or 60 for something that
  // ends up looking like water. Initialize our coordinates
  uint16_t x{math::random::Int16()};
  uint16_t y{math::random::Int16()};
  uint16_t z{math::random::Int16()};

  NoiseGenerator(const math::Dimension& size, float speed = 20)
      : size{size}, speed{speed} {
    data = new uint8_t*[size.x];
    for (size_t i = 0; i < size.y; i++) {
      data[i] = new uint8_t[size.y];
    }
  }

  // Fill the x/y array of 8-bit noise values using the inoise8 function.
  void fillnoise8() {
    const auto now = millis();

    // Adjust our speed based on our timing
    if (lastFrameMillis != 0) {
      // Get a ratio of actual framerate vs expected
      // assuming we had a framerate of 40 milliseconds...
      const static float expectedFrameRateMillis = 40.0;
      const float timeFactor =
          (float)(now - lastFrameMillis) / expectedFrameRateMillis;

      z += speed * timeFactor;
    }
    lastFrameMillis = now;

    for (size_t i = 0; i < size.x; i++) {
      int ioffset = scale * i;
      for (size_t j = 0; j < size.y; j++) {
        int joffset = scale * j;
        data[i][j] = inoise8(x + ioffset, y + joffset, z);
      }
    }
  }
};

}  // namespace engines
}  // namespace kss
