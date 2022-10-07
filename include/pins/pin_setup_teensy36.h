#pragma once

#include "serial/debug.h"  // for Debug

namespace kss {
namespace pins {

// Leds: 18 only
constexpr size_t LedCount{1};
constexpr uint8_t Leds[LedCount]{18};

constexpr size_t LedInstructoCount{1};
constexpr uint8_t LedInstructo[LedInstructoCount]{Leds[0]};

void Init() {
  // Set Led pins to output mode
  for (const auto pin : Leds) {
    pinMode(pin, OUTPUT);
  }

  Debug("Pinout initialized for Teensy3.6 configuration");
}

}  // namespace pins
}  // namespace kss
