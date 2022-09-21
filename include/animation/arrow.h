#pragma once

#include "animation/animation.h"   // for Animation
#include "display/display.h"       // for Display
#include "engines/physics_info.h"  // for PhysicsInfo
#include "math/vector2d.h"         // for Dimension
#include "serial/debug.h"          // for Debug

namespace kss {
namespace animation {

class Arrow : public Animation {
  static constexpr size_t arrow_height{5};

 public:
  engines::PhysicsInfo physics;

  uint32_t desired_time;
  size_t desired_y;

  Arrow(size_t y, size_t desired_y, uint32_t desired_time)
      : Animation(), desired_time{desired_time}, desired_y{desired_y} {
    physics.location.y = y;
    physics.respect_edges = false;
  }

  // TODO remove this for dynamic allocation
  void Initialize(size_t y, size_t desired_y, uint32_t desired_time) {
    this->desired_time = desired_time;
    this->desired_y = desired_y;
    physics.location.y = y;
    UpdatePhysics();
    Debug("y=" + physics.location.y + ", d_y=" + desired_y + ", d_t=" +
          desired_time + ", t=" + millis() + ", v=" + physics.velocity.y);
  }

  inline float GetY() const { return physics.location.y; }

  bool IsDone() {
    return physics.location.y + (float)arrow_height < 0;
  }

  void UpdatePhysics() {
    const uint32_t now = millis();
    if (desired_time <= now || physics.location.y <= desired_y) {
      Debug("Overshoot: t=" + now + " target_t=" + desired_time +
            ", y=" + physics.location.y + " target_y=" + desired_y);
      return;
    }

    const float time_diff = (desired_time - now) / 1000.0f;
    const float y_diff = physics.location.y - desired_y;
    physics.velocity.y = -y_diff / (float)time_diff;
  }

  void Move() override {
    if (IsDone()) {
      return;
    }
    UpdatePhysics();
    physics.Move();
  }

  void drawPixel(display::Display* display, math::Dimension point) {
    if (display->IsInBounds(point)) {
      auto& pixel = display->Pixel(point);
      // Convert pixel to HSV and rotate hue 180 degrees
      const auto hsv_pixel = rgb2hsv_approximate(pixel);
      const auto hue = (128 + hsv_pixel.hue) % 256;  // rotate
      const auto val = (255 + hsv_pixel.val) / 2;    // skew bright
      pixel.setHSV(hue, hsv_pixel.sat, val);
    }
  }

  void draw(display::Display* display) override {
    for (size_t y = 0; y < 3; ++y) {
      for (size_t x = y; x < y + 3; ++x) {
        drawPixel(display, {x, physics.location.y + y});
        drawPixel(display, {x, physics.location.y - y});
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
