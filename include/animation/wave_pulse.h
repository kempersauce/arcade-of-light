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
  float y;

  // Default contructor - opacity = 0 since we have no details
  WavePulse() : Animation(), opacity{0} {}

  WavePulse(size_t height, size_t edge_trim, CRGB color)
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
    const float y_decimal = fmod(y, 1);
    const size_t other_edge = display->size.width - edge_trim;
    for (size_t y_offset = 0; y_offset < height; ++y_offset) {
      const float y_offset_f = (float)y_offset + y_decimal;
      const float presence =
          opacity * ((float)height - y_offset_f) / (float)height;
      const float y_adjusted = fmod(y + y_offset_f, display->size.height);
      for (size_t x = edge_trim; x < other_edge; ++x) {
        if (y_offset == 0) {
          display->DitherPixelY(x, y_adjusted - 1, color, presence);
        }
        display->BlendPixel(x, y_adjusted, color, presence);
      }

      // Push edges back to give a cool curve to the wave
      const float y_edge = fmod(y_adjusted + 0.75f, display->size.height);
      //   const float y_edge = y_adjusted; // xXx_straight_edge_xXx
      if (y_offset == 0) {
        display->DitherPixelY(edge_trim - 1, y_edge - 1, color,
                              edge_blend * presence);
        display->DitherPixelY(other_edge, y_edge - 1, color,
                              edge_blend * presence);
      }
      display->BlendPixel(edge_trim - 1, y_edge, color, edge_blend * presence);
      display->BlendPixel(other_edge, y_edge, color, edge_blend * presence);
    }
  }
};

}  // namespace animation
}  // namespace kss
