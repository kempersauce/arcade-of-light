#pragma once

#include <pixeltypes.h>  // for CRGB

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

class WavePulse : public Animation {
  size_t height;
  size_t edge_trim;
  float edge_blend{0.5f};

 public:
  float fade_per_milli{0.0f};
  CRGB color;
  float opacity{1.0f};
  size_t y;

  WavePulse() : Animation(), opacity{0} {}
  WavePulse(size_t height, CRGB color, size_t edge_trim = 0)
      : Animation(), height{height}, edge_trim{edge_trim + 1}, color{color} {}

  void Move() override {
    if (fade_per_milli != 0 && opacity > 0) {
      opacity -= time::LoopElapsedMillis() * fade_per_milli;
      if (opacity <= 0) {
        opacity = 0;
      }
    }
  }

  void Draw(display::Display* display) override {
    if (opacity <= 0) {
      return;
    }
    const size_t other_edge = display->size.width - edge_trim;
    for (size_t y_offset = 0; y_offset < height; ++y_offset) {
      const float presence = opacity * (float)(height - y_offset) / (float)height;
      const size_t y_adjusted = (y + y_offset) % display->size.height;
      for (size_t x = edge_trim; x < other_edge; ++x) {
        display->BlendPixel(x, y_adjusted, color, presence);
      }
      display->BlendPixel(edge_trim - 1, y_adjusted, color,
                          edge_blend * presence);
      display->BlendPixel(other_edge, y_adjusted, color, edge_blend * presence);
    }
  }
};

}  // namespace animation
}  // namespace kss
