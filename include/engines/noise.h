#pragma once

#include <FastLED.h>  // for time::Now()

#include "math/random.h"    // for random::*
#include "math/vector2d.h"  // for Dimension
#include "time/now.h"       // for Now

namespace kss {
namespace engines {

class NoiseGenerator {
  const math::Dimension size;

  inline size_t DataIndex(const size_t x, const size_t y) const {
    return x * size.height + y;
  }

  // This is the array that we keep our computed noise values in
  // We make it public so our consumers can directly access our nouse matrix
  uint8_t* const data;

 public:
  // Notes about speed:
  // 1: almost looks like a painting, moves very slowly
  // 20: (default) a nice starting speed, mixes well with a scale of 100
  // 100: wicked fast!
  const float speed;

  // Scale determines how far apart the pixels in our noise matrix are.  Try
  // changing these values around to see how it affects the motion of the
  // display->  The higher the value of scale, the more "zoomed out" the noise
  // iwll be.  A value of 1 will be so zoomed in, you'll mostly see solid
  // colors.

  // const uint16_t scale = 1; // mostly just solid colors
  // const uint16_t scale = 4011; // very zoomed out and shimmery
  const uint16_t scale = 1024;

  // We're using the x/y dimensions to map to the x/y pixels on the matrix.
  // We'll use the z-axis for "time".  speed determines how fast time moves
  // forward.  Try 1 for a very slow moving effect, or 60 for something that
  // ends up looking like water. Initialize our coordinates
  uint16_t x{math::random::Int16()};
  uint16_t y{math::random::Int16()};
  uint16_t z{math::random::Int16()};

  // Default constructor
  NoiseGenerator() : size{0, 0}, data{NULL}, speed{0} {}
  NoiseGenerator(const math::Dimension size, float speed = 20)
      : size{size}, data{new uint8_t[size.width * size.height]}, speed{speed} {}

  uint8_t Data(const size_t x, const size_t y) const {
    return data[DataIndex(x, y)];
  }

  // Fill the x/y array of 8-bit noise values using the inoise8 function.
  uint32_t last_filled_millis{0};
  void fillnoise8() {
    // Skip if we already ran this frame
    if (last_filled_millis == time::Now()) {
      return;
    }
    last_filled_millis = time::Now();

    // Adjust our speed based on our timing
    const static float expectedFrameRateMillis = 40.0;
    const float timeFactor =
        (float)time::LoopElapsedMillis() / expectedFrameRateMillis;

    z += speed * timeFactor;

    for (size_t i = 0; i < size.x; i++) {
      const size_t x_loc = x + scale * i;
      for (size_t j = 0; j < size.y; j++) {
        const size_t y_loc = y + scale * j;
        data[DataIndex(i, j)] = inoise8(x_loc, y_loc, z);
      }
    }
  }
};

}  // namespace engines
}  // namespace kss
