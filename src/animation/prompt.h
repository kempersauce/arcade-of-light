#pragma once

#include "animation/animation.h"   // for Animation
#include "display/display.h"       // for Display
#include "engines/physics_info.h"  // for PhysicsInfo
#include "math/vector2d.h"         // for Dimension
#include "serial/debug.h"          // for Debug
#include "time/now.h"              // for Now

namespace kss {
namespace animation {

class Prompt : public Animation {
  static constexpr size_t prompt_height{5};

 public:
  // TODO reorder these to match pins for consistency
  enum Direction { LEFT, RIGHT, UP, DOWN } direction;

  engines::PhysicsInfo physics;

  uint32_t desired_time;
  size_t desired_y;

  Prompt(Direction direction, size_t y, size_t desired_y, uint32_t desired_time)
      : Animation(),
        direction{direction},
        desired_time{desired_time},
        desired_y{desired_y} {
    physics.location.y = y;
    physics.respect_edges = false;
  }

  inline float GetY() const { return physics.location.y; }

  bool IsDone() { return physics.location.y < 0; }

  void UpdatePhysics() {
    const uint32_t now = time::Now();
    if (desired_time <= now || physics.location.y <= desired_y) {
      Debug("Overshoot: t=" + now + " target_t=" + desired_time +
            ", y=" + physics.location.y + " target_y=" + desired_y);
      return;
    }

    // const float time_diff = (desired_time - now) / 1000.0f;
    const float time_diff = desired_time - now;
    const float y_diff = physics.location.y - desired_y;
    physics.velocity.y = -y_diff / time_diff;
  }

  void Move() override {
    if (IsDone()) {
      Debug("Prompt IsDone(), should be deleted!");
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

  void DrawLeft(display::Display* display) {
    for (size_t y = 0; y < 3; ++y) {
      for (size_t x = y; x < y + 3; ++x) {
        drawPixel(display, {x, physics.location.y + y});
        drawPixel(display, {x, physics.location.y - y});
      }
    }
  }

  void DrawRight(display::Display* display) {
    drawPixel(display, {1, physics.location.y + 2});
    drawPixel(display, {2, physics.location.y + 1});
    drawPixel(display, {3, physics.location.y});
    drawPixel(display, {2, physics.location.y - 1});
    drawPixel(display, {1, physics.location.y - 2});
  }

  void DrawUp(display::Display* display) {
    drawPixel(display, {0, physics.location.y - 1});
    drawPixel(display, {1, physics.location.y});
    drawPixel(display, {2, physics.location.y + 1});
    drawPixel(display, {3, physics.location.y});
    drawPixel(display, {4, physics.location.y - 1});
  }

  void DrawDown(display::Display* display) {
    drawPixel(display, {0, physics.location.y + 1});
    drawPixel(display, {1, physics.location.y});
    drawPixel(display, {2, physics.location.y - 1});
    drawPixel(display, {3, physics.location.y});
    drawPixel(display, {4, physics.location.y + 1});
  }

  void Draw(display::Display* display) override {
    switch (direction) {
      case LEFT:
        DrawLeft(display);
        break;

      case RIGHT:
        DrawRight(display);
        break;

      case UP:
        DrawUp(display);
        break;

      case DOWN:
        DrawDown(display);
        break;
    }
  }
};

}  // namespace animation
}  // namespace kss
