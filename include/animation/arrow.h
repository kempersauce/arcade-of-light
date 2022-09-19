#pragma once

#include <vector>  // for vector

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "math/arrows.h"          // for Arrow*
#include "math/shape.h"           // for Shape
#include "math/vector2d.h"        // for Dimension

namespace kss {
namespace animation {

namespace _arrow {
// const math::Shape* LeftArrow = new math::Shape(math::shapes::ArrowLeftFull());
// const math::Shape* RightArrow = new math::Shape(math::shapes::ArrowRightFull());
// const math::Shape* UpArrow = new math::Shape(math::shapes::ArrowUpFull());
// const math::Shape* DownArrow = new math::Shape(math::shapes::ArrowDownFull());
}  // namespace _arrow
using namespace _arrow;

class Arrow : public Animation {
  const math::Shape* shape = new math::Shape(math::shapes::ArrowLeftFull());
  const math::Shape* shapeR = new math::Shape(math::shapes::ArrowRightFull());
  const math::Shape* shapeU = new math::Shape(math::shapes::ArrowUpFull());
  const math::Shape* shapeD = new math::Shape(math::shapes::ArrowDownFull());

 public:
  enum Stage { NOT_STARTED, PLAYING, DONE } stage;

  math::Dimension location;

  Arrow() : Animation() {}

  virtual void draw(display::Display* display) override {
    for (const auto& offset : shape->points) {
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
