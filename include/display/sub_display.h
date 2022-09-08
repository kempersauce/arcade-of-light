#pragma once

#include <FastLED.h>  // for CRGB

#include "display/display.h"  // for Display
#include "math/vector2d.h"    // for Dimension
#include "serial/debug.h"     // for debug::*

/*
Display Class
holds the strips
*/

namespace kss {
namespace display {

class SubDisplay : public Display {
  Display* const parent;
  const math::Dimension location;

 public:
  SubDisplay(Display* parent, const math::Dimension& location,
             const math::Dimension& size)
      : Display(size), parent{parent}, location{location} {
    debug::println((String) "SubDisplay: loc=" + location.x + "x" + location.y +
                   ", size=" + size.x + "x" + size.y);
  }

  virtual inline CRGB& Pixel(const size_t strip, const size_t pixel) override {
#ifdef DEBUG
    // Run initial checking on this SubDisplay to detect bleedover
    CheckLocation(strip, pixel);
#endif
    return parent->Pixel(strip + location.x, pixel + location.y);
  };

  virtual void Show() override {
    // Should we activate this? Maybe these shouldn't show individually
    // parent->Show();
  }
};

}  // namespace display
}  // namespace kss
