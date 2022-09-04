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

class Panel : public Display {
  Display* parent;
  const size_t strip_offset;

 public:
  Panel(Display* parent, const math::Dimension& size,
        const size_t strip_offset)
      : Display(size),
        parent{parent},
        strip_offset{strip_offset} {}

  virtual inline CRGB& Pixel(const size_t strip, const size_t pixel) override {
#ifdef DEBUG
    // Run initial checking on this panel to detect bleedover
    CheckLocation(strip, pixel);
#endif
    return parent->Pixel(strip + strip_offset, pixel);
  };

  virtual void Show() override {
    // Should we activate this? Maybe these shouldn't show individually
    // parent->Show();
  }
};

}  // namespace display
}  // namespace kss
