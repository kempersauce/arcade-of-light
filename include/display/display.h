#pragma once

#include <FastLED.h>  // for CRGB

#include "math/vector2d.h"  // for Dimension
#include "serial/debug.h"   // for debug::*

/*
Display Class
holds the strips
*/

namespace kss {
namespace display {

void Blend(CRGB& pixel, const CRGB* blend_color, const float blend_factor) {
  const auto unblend_factor = 1 - blend_factor;

  // get weighted blend values
  const uint8_t red =
      pixel.red * unblend_factor + blend_color->red * blend_factor;
  const uint8_t green =
      pixel.green * unblend_factor + blend_color->green * blend_factor;
  const uint8_t blue =
      pixel.blue * unblend_factor + blend_color->blue * blend_factor;

  // set the new values onto the pixel
  pixel.setRGB(red, green, blue);
}

class Display {
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
  void BlendPixel(const size_t x, const size_t y, const CRGB* blend_color,
                  const float blend_factor) {
    if (CheckLocation(x, y)) {
      Blend(Pixel(x, y), blend_color, blend_factor);
    }
  }

  // Dither the pixels on the strip above and below y, blending them to color
  void DitherPixel(const size_t stripIndex, const float y, const CRGB* color,
                   const float blend_factor = 1) {
    const size_t y_int = y;
    const float dither = y - y_int;
    BlendPixel(stripIndex, y_int, color, (1 - dither) * blend_factor);
    BlendPixel(stripIndex, y_int + 1, color, dither * blend_factor);
  }

  inline bool IsInBounds(const size_t strip, const size_t pixel) const {
    return strip >= 0 && strip < size.x && pixel >= 0 && pixel < size.y;
  }

  inline bool IsInBounds(const math::Dimension& point) const {
    return IsInBounds(point.x, point.y);
  }

 protected:
  inline bool CheckLocation(const size_t strip, const size_t pixel) const {
    const bool oob = !IsInBounds(strip, pixel);
#ifdef DEBUG
    if (oob) {
      if (size.x == 0 || size.y == 0) {
        debug::print((String) "ERROR: Ill-defined display");
      } else {
        debug::print((String) "ERROR: Accessing out of bounds pixel");
      }
      debug::println((String) ": loc=" + strip + "x" + pixel +
                     ", display=" + size.x + "x" + size.y);
    }
#endif
    return !oob;
  }
};

}  // namespace display
}  // namespace kss
