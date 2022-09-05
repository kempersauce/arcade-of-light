#pragma once

#include "display/display.h"  // for Display
#include "display/panel.h"    // for Panel
#include "display/twenty.h"   // for TwentyDisplay

namespace kss {
namespace display {

class FourPanelDisplay : public TwentyDisplay {
  const size_t panel_width;

 public:
  Panel panels[4];

  FourPanelDisplay()
      : TwentyDisplay(),
        panel_width{size.x / 4},
        panels{{this, {panel_width, size.y}, 0 * panel_width},
               {this, {panel_width, size.y}, 1 * panel_width},
               {this, {panel_width, size.y}, 2 * panel_width},
               {this, {panel_width, size.y}, 3 * panel_width}} {}
};

}  // namespace display
}  // namespace kss
