#pragma once

#include "display/display.h"      // for Display
#include "display/octo/twenty.h"  // for TwentyDisplay
#include "display/sub_display.h"  // for SubDisplay

namespace kss {
namespace display {
namespace octo {

// This is a demo class, it was meant to be used but we may not actually use it
class FourPanelDisplay : public TwentyDisplay {
  const size_t panel_width;

 public:
  SubDisplay panels[4];

  FourPanelDisplay()
      : TwentyDisplay(),
        panel_width{size.x / 4},
        panels{{this, {0 * panel_width, 0}, {panel_width, size.y}},
               {this, {1 * panel_width, 0}, {panel_width, size.y}},
               {this, {2 * panel_width, 0}, {panel_width, size.y}},
               {this, {3 * panel_width, 0}, {panel_width, size.y}}} {}
};

}  // namespace octo
}  // namespace display
}  // namespace kss
