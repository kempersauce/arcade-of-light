#pragma once

#include <FastLED.h>  // for time::Now()

#include "math/random.h"    // for random::*
#include "math/vector2d.h"  // for Dimension
#include "math/vector3d.h"  // for Vector3D
#include "time/now.h"       // for Now

namespace kss {
namespace engines {

class NoiseGenerator {
  constexpr static float expectedFrameRateMillis = 40.0;
  const math::Dimension size;

  inline const size_t GetIndex(size_t x, size_t y) const {
    return x * size.height + y;
  }

 public:
  // Notes about speed:
  // 1: almost looks like a painting, moves very slowly
  // 20: (default) a nice starting speed, mixes well with a scale of 100
  // 100: wicked fast!
  math::Vector3D<float> speed;

  // Scale determines how far apart the pixels in our noise matrix are.  Try
  // changing these values around to see how it affects the motion of the
  // display->  The higher the value of scale, the more "zoomed out" the noise
  // iwll be.  A value of 1 will be so zoomed in, you'll mostly see solid
  // colors.

  // const uint16_t scale = 1; // mostly just solid colors
  // const uint16_t scale = 4011; // very zoomed out and shimmery
  const uint16_t scale = 1024;

  // This is the array that we keep our computed noise values in
  // We make it public so our consumers can directly access our nouse matrix
  uint8_t* data;

  // We're using the x/y dimensions to map to the x/y pixels on the matrix.
  // We'll use the z-axis for "time".  speed determines how fast time moves
  // forward.  Try 1 for a very slow moving effect, or 60 for something that
  // ends up looking like water. Initialize our coordinates
  math::Vector3D<uint16_t> coordinates{
      math::random::Int16(), math::random::Int16(), math::random::Int16()};

  NoiseGenerator(math::Dimension size, float speed = 20)
      : size{size}, speed{0, 0, speed / (scale * expectedFrameRateMillis)} {
    data = new uint8_t[size.width * size.height];
  }

  uint8_t Data(size_t x, size_t y) const { return data[GetIndex(x, y)]; }

  // Fill the x/y array of 8-bit noise values using the inoise8 function.
  void fillnoise8() {
    // Adjust our coordinates based on our timing & speed
    coordinates += speed * (scale * time::LoopElapsedMillis());

    for (size_t i = 0; i < size.width; ++i) {
      const uint16_t scaled_x = coordinates.x + scale * i;
      for (size_t j = 0; j < size.height; ++j) {
        const uint16_t scaled_y = coordinates.y + scale * j;
        data[GetIndex(i, j)] = inoise8(scaled_x, scaled_y, coordinates.z);
      }
    }
  }
};

}  // namespace engines
}  // namespace kss
