#pragma once

#include <FastLED.h>  // for CRGB

#include "serial/debug.h"  // for debug::*

/*
Display Class
holds the strips
*/

namespace kss {
namespace display {

class Display {
 public:
  const size_t numStrips;
  const size_t lengthStrips;

  Display(const size_t numberOfStrips, const size_t lengthOfStrips)
      : numStrips(numberOfStrips), lengthStrips(lengthOfStrips) {}

  virtual inline CRGB& Pixel(const size_t strip, const size_t pixel) = 0;

  void blendPixel(int x, int y, CRGB* blend_color, float blend_factor) {
    if (y >= 0 && y < lengthStrips) {
      CRGB& pixel = Pixel(x, y);
      const auto unblend_factor = 1 - blend_factor;

      // get weighted blend values values
      const auto red =
          pixel.red * unblend_factor + blend_color->red * blend_factor;
      const auto green =
          pixel.green * unblend_factor + blend_color->green * blend_factor;
      const auto blue =
          pixel.blue * unblend_factor + blend_color->blue * blend_factor;

      // set the new values onto the pixel
      pixel.setRGB(red, green, blue);
    }
  }

  void ditherPixel(int stripIndex, float y, CRGB* color,
                   float blend_factor = 1) {
    const int y_int = y;
    const float dither = y - y_int;
    blendPixel(stripIndex, y_int, color, (1 - dither) * blend_factor);
    blendPixel(stripIndex, y_int + 1, color, dither * blend_factor);
  }

 protected:
  inline bool CheckLocation(size_t strip, size_t pixel) {
    bool oob =
        strip < 0 || strip >= numStrips || pixel < 0 || pixel >= lengthStrips;
#ifdef DEBUG
    if (oob) {
      debug::println("ERROR: Accessing out of bounds pixel");
      debug::println((String) "strip: " + strip + " (max: " + (numStrips - 1) +
                     ")");
      debug::println((String) "pixel: " + pixel +
                     " (max: " + (lengthStrips - 1) + ")");
    }
#endif
    return !oob;
  }
};

}  // namespace display
}  // namespace kss
