#pragma once

#include "animation/animation.h"  // for Animation
#include "animation/starscape.h"  // for Starscape
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

class WavePulseStars : public Animation {
  const size_t height;
  Starscape stars;

 public:
  size_t y;

  WavePulseStars(size_t height, math::Dimension screen_size)
      : Animation(), height{height}, stars{screen_size, 85} {}

  void Move() override { stars.Move(); }

  void Draw(display::Display* display) {
    for (size_t i = 0; i < height; ++i) {
      const float presence = (float)(height - i) / (float)height;
      for (size_t x = 0; x < display->size.width; ++x) {
        const size_t y_adjusted = (y + i) % display->size.height;
        CRGB color = stars.GetPixel(x, y_adjusted);
        display->BlendPixel(x, y_adjusted, color, presence);
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
