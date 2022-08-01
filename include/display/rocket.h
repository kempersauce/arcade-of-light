#pragma once

#include <Constants.h>

#include "display/standard_display.h"  // for StandardDisplay

namespace kss {
namespace display {

class RocketDisplay : public StandardDisplay<3, 300> {
 public:
  RocketDisplay() : StandardDisplay() {
    RegisterStrip<20>(0);
    RegisterStrip<17>(1);
    RegisterStrip<16>(2);
  }
};

}  // namespace display
}  // namespace kss
