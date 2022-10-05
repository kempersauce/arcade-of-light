#pragma once

#include "animation/animation.h"  // for Animation
#include "animation/starscape.h"  // for Starscape
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

class WavePulseStars : public Animation {
  const size_t height;
  Starscape stars;

  const size_t edge_trim;
  const float edge_blend{0.5f};

 public:
  size_t y;

  WavePulseStars(size_t height, size_t edge_trim, math::Dimension screen_size,
                 uint8_t hue)
      : Animation(),
        height{height},
        stars{screen_size, 85},
        edge_trim{edge_trim + 1} {
    stars.hue = hue;
  }

  void Move() override { stars.Move(); }

  void Draw(display::Display* display) override {
    const size_t other_edge = display->size.width - edge_trim;
    for (size_t y_offset = 0; y_offset < height; ++y_offset) {
      const float presence = (float)(height - y_offset) / (float)height;
      const size_t y_adjusted = (y + y_offset) % display->size.height;
      for (size_t x = edge_trim; x < other_edge; ++x) {
        CRGB color = stars.GetPixel(x, y_adjusted);
        display->BlendPixel(x, y_adjusted, color, presence);
      }
      display->BlendPixel(edge_trim - 1, y_adjusted,
                          stars.GetPixel(edge_trim - 1, y_adjusted),
                          edge_blend * presence);
      display->BlendPixel(other_edge, y_adjusted,
                          stars.GetPixel(other_edge, y_adjusted),
                          edge_blend * presence);
    }
  }
};

}  // namespace animation
}  // namespace kss
