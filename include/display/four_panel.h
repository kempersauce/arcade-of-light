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
        panel_width{strip_count / 4},
        panels{{this, panel_width, strip_length, 0 * panel_width},
               {this, panel_width, strip_length, 1 * panel_width},
               {this, panel_width, strip_length, 2 * panel_width},
               {this, panel_width, strip_length, 3 * panel_width}} {}
};

}  // namespace display
}  // namespace kss
