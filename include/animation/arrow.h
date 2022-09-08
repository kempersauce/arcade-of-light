#pragma once

#include <vector>  // for vector

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "math/shape.h"           // for Shape
#include "math/vector2d.h"        // for Dimension

namespace kss {
namespace animation {

// // ARROW SHAPE
// //  0 1 2 3 4
// // | | |#|#|#| 4
// // | |#| |#| | 3
// // |#| |#| | | 2
// // | |#| |#| | 1
// // | | |#|#|#| 0
// // const math::Shape left{{
// // {2, 4}, {3, 4}, {4, 4},
// // {1, 3}, {3, 3},
// // {0, 2}, {2, 2},
// // {1, 1}, {3, 1},
// // {2, 0}, {3, 0}, {4, 0}
// // }};

// // ARROW SHAPE
// //  0 1 2 3 4
// // | | |#|#|#| 4
// // | |#|#|#| | 3
// // |#|#|#| | | 2
// // | |#|#|#| | 1
// // | | |#|#|#| 0
const math::Shape left{{
{2, 4}, {3, 4}, {4, 4},
{1, 3}, {2, 3}, {3, 3},
{0, 2}, {1, 2}, {2, 2},
{1, 1}, {2, 1}, {3, 1},
{2, 0}, {3, 0}, {4, 0}
}};

// const math::Shape right{left.FlipX()};
// const math::Shape up{left.RotateClock()};
// const math::Shape down{left.RotateCounterClock()};

class Arrow : public Animation {
  math::Shape shape{left};

 public:
  math::Dimension location;

  Arrow() : Animation() {}

  virtual void draw(display::Display* display) override {
    for (const auto& offset : shape.points) {
      const auto point = location + offset;
      if (display->IsInBounds(point)) {
        auto& pixel = display->Pixel(point);
        // Convert pixel to HSV and rotate hue 180 degrees
        const auto hsv_pixel = rgb2hsv_approximate(pixel);
        const auto hue = (128 + hsv_pixel.hue) % 256;  // rotate
        const auto val = (255 + hsv_pixel.val) / 2;    // skew bright
        pixel.setHSV(hue, hsv_pixel.sat, val);
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
