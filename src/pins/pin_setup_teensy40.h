#pragma once

#include <Arduino.h>  // for digitalRead, pinMode

#include "serial/debug.h"  // for Debug

namespace kss {
namespace pins {

// Dips: 2-5
constexpr uint8_t Dips[]{2, 3, 4, 5};

// Read the value of the corresponding DipSwitch pin
inline uint8_t ReadDipRaw(const size_t dip_index) {
  return digitalRead(Dips[dip_index]);
}

// Return the value of the corresponding DipSwitch pin as a boolean
inline bool ReadDip(const size_t dip_index) {
  return ReadDipRaw(dip_index) == 0;
}

void Init() {
  // Set dip switch pins to input mode
  for (const auto pin : Dips) {
    pinMode(pin, INPUT);
  }

  Debug("Pinout initialized for Teensy4.0 configuration");
  Debug("DipSwitches=[" + ReadDipRaw(0) + ReadDipRaw(1) + ReadDipRaw(2) +
        ReadDipRaw(3) + "]");
}

// AUDIO
// We dont have an audio volume pin....
// #define AUDIO_VOLUME_PIN 13

}  // namespace pins
}  // namespace kss
