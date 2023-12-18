#pragma once

#include "display/display.h"      // for Display
#include "display/octo/twenty.h"  // for TwentyDisplay
#include "display/sub_display.h"  // for SubDisplay

namespace kss {
namespace display {
namespace octo {

// This is a demo class, it was meant to be used but we may not actually use it
class FourPanelDisplay : public TwentyDisplay {
 public:
  const math::Dimension panel_size;
  SubDisplay panels[4];

  FourPanelDisplay(bool is_grb = true)
      : TwentyDisplay(is_grb),
        panel_size{size.x / 4, size.y},
        panels{{this, {0 * panel_size.width, 0}, panel_size},
               {this, {1 * panel_size.width, 0}, panel_size},
               {this, {2 * panel_size.width, 0}, panel_size},
               {this, {3 * panel_size.width, 0}, panel_size}} {}
};

}  // namespace octo
}  // namespace display
}  // namespace kss
