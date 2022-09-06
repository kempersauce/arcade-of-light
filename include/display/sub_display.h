#pragma once

#include <FastLED.h>  // for CRGB

#include "display/display.h"  // for Display
#include "serial/debug.h"     // for debug::*

/*
Display Class
holds the strips
*/

namespace kss {
namespace display {

class SubDisplay : public Display {
  Display& parent;
  const math::Dimension location;

 public:
  SubDisplay(Display& parent, const math::Dimension& location, const math::Dimension& size)
      : Display(size),
        parent{parent},
        location{location} {}

  virtual inline CRGB& Pixel(const size_t strip, const size_t pixel) override {
#ifdef DEBUG
    // Run initial checking on this SubDisplay to detect bleedover
    CheckLocation(strip, pixel);
#endif
    return parent.Pixel(strip + location.x, pixel + location.y);
  };

  virtual void Show() override {
    // Should we activate this? Maybe these shouldn't show individually
    // parent->Show();
  }
};

}  // namespace display
}  // namespace kss
