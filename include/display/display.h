#pragma once

#include <FastLED.h>  // for CRGB

#include "math/vector2d.h"  // for Dimension
#include "serial/debug.h"   // for Debug

/*
Display Class
holds the strips
*/

namespace kss {
namespace display {

void Blend(CRGB& pixel, const CRGB color, const float blend_factor) {
  const float unblend_factor = 1 - blend_factor;

  // get weighted blend values
  const uint8_t r = pixel.r * unblend_factor + color.r * blend_factor;
  const uint8_t g = pixel.g * unblend_factor + color.g * blend_factor;
  const uint8_t b = pixel.b * unblend_factor + color.b * blend_factor;

  // set the new values onto the pixel
  pixel.setRGB(r, g, b);
}

class Display {
 protected:
  CRGB dummy_pixel;

 public:
  const math::Dimension size;

  Display(const math::Dimension& size) : size{size} {}
  virtual ~Display() = default;

  // Reference to the desired CRGB pixel for get/set and other operations
  virtual inline CRGB& Pixel(const size_t strip, const size_t pixel) = 0;

  inline CRGB& Pixel(const math::Dimension& point) {
    return Pixel(point.x, point.y);
  }

  // Draw this Display object's contents to the LED strips
  virtual void Show() = 0;

  // Blend the pixel at (x, y) with blend_color according to a blend_factor
  void BlendPixel(const size_t x, const size_t y, const CRGB blend_color,
                  const float blend_factor) {
    if (CheckLocation(x, y)) {
      Blend(Pixel(x, y), blend_color, blend_factor);
    }
  }

  // Dither the pixels on the strip left and right of x, blending them to color
  void DitherPixelX(const float x, const size_t y, const CRGB color,
                    const float blend_factor = 1) {
    const size_t x_int = x;
    const float dither = x - x_int;
    BlendPixel(x_int, y, color, (1 - dither) * blend_factor);
    BlendPixel(x_int + 1, y, color, dither * blend_factor);
  }

  // Dither the pixels on the strip above and below y, blending them to color
  void DitherPixelY(const size_t x, const float y, const CRGB color,
                    const float blend_factor = 1) {
    const size_t y_int = y;
    const float dither = y - y_int;
    BlendPixel(x, y_int, color, (1 - dither) * blend_factor);
    BlendPixel(x, y_int + 1, color, dither * blend_factor);
  }

  inline bool IsInBounds(const size_t strip, const size_t pixel) const {
    return strip >= 0 && strip < size.x && pixel >= 0 && pixel < size.y;
  }

  inline bool IsInBounds(const math::Dimension& point) const {
    return IsInBounds(point.x, point.y);
  }

 protected:
  inline bool CheckLocation(const size_t strip, const size_t pixel) const {
    const bool in_bounds = IsInBounds(strip, pixel);
    // if (!in_bounds) {
    //   if (size.x == 0 || size.y == 0) {
    //     Debug("ERROR: Ill-defined display: loc=" + strip + "x" + pixel +
    //           ", display=" + size.x + "x" + size.y);
    //   } else {
    //     Debug("ERROR: Accessing out of bounds pixel: loc=" + strip + "x" +
    //           pixel + ", display=" + size.x + "x" + size.y);
    //   }
    // }
    return in_bounds;
  }
};

}  // namespace display
}  // namespace kss
