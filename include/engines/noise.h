#pragma once

#include <FastLED.h>  // for millis()

#include "engines/random.h"  // for random::*

namespace kss {
namespace engines {

class NoiseGenerator {
  uint32_t lastFrameMillis;

  const size_t width;
  const size_t height;

 public:
  // Notes about speed:
  // 1: almost looks like a painting, moves very slowly
  // 20: (default) a nice starting speed, mixes well with a scale of 100
  // 100: wicked fast!
  const uint16_t speed;

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
  uint16_t x = engines::random::Int16();
  uint16_t y = engines::random::Int16();
  uint16_t z = engines::random::Int16();

  NoiseGenerator(size_t width, size_t height, uint16_t speed = 20)
      : width{width}, height{height}, speed{speed} {
    data = new uint8_t*[width];
    for (size_t i = 0; i < height; i++) {
      data[i] = new uint8_t[height];
    }
  }

  // Fill the x/y array of 8-bit noise values using the inoise8 function.
  void fillnoise8() {
    // assuming we had a framerate of 30 milliseconds...
    const static float expectedFrameRateMillis = 40.0;

    // Get a ratio of actual framerate vs expected
    const auto now = millis();
    float timeFactor = (float)(now - lastFrameMillis) / expectedFrameRateMillis;
    lastFrameMillis = now;

    // adjust our speed based on our timing
    z += (float)speed * timeFactor;

    for (size_t i = 0; i < width; i++) {
      int ioffset = scale * i;
      for (size_t j = 0; j < height; j++) {
        int joffset = scale * j;
        data[i][j] = inoise8(x + ioffset, y + joffset, z);
      }
    }
  }
};

}  // namespace engines
}  // namespace kss
