#pragma once

#include "serial/debug.h"  // for Debug

namespace kss {
namespace pins {

constexpr uint8_t Leds[]{12};

void Init() {
  // TODO set up output mode for LEDs?

  Debug("Pinout initialized for Teensy3.6 configuration");
}

}  // namespace pins
}  // namespace kss
