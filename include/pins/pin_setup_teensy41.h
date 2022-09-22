#pragma once

#include <Arduino.h>  // for digitalRead, pinMode

#include "serial/debug.h"  // for Debug

namespace kss {
namespace pins {

// Controller selector lines: 2-4, 7
// With Dip0 set ON, these are instead 2-5
uint8_t Controllers[]{2, 3, 4, 7};

// Button read pins: 8-13
// With Dip0 set ON, these are instead 6, 9-13
uint8_t Buttons[]{8, 9, 10, 11, 12, 13};

// Leds: 18-37
constexpr uint8_t Leds[]{18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
                         28, 29, 30, 31, 32, 33, 34, 35, 36, 37};

constexpr uint8_t LedInstructo{Leds[12]};

// Dips: 38-41
constexpr uint8_t Dips[]{38, 39, 40, 41};

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

  // Dip0 "ON" (==0) means we switch these pins for frankenstein boards
  bool frankenstein_mode = ReadDip(0);
  if (frankenstein_mode) {
    Controllers[3] = 5;
    Buttons[0] = 6;
  }

  // TODO Set pinMode for Leds?

  // Set controller pins to output mode
  for (const auto pin : Controllers) {
    pinMode(pin, OUTPUT);
  }

  // Set button pins to input mode
  for (const auto pin : Buttons) {
    pinMode(pin, INPUT);
  }

  Debug("Pinout initialized for Teensy4.1 configuration");
  if (frankenstein_mode) {
    Debug("Configured for Frankenstein Mode");
  }

  Debug("DipSwitches=[" + ReadDipRaw(0) + ReadDipRaw(1) + ReadDipRaw(2) +
        ReadDipRaw(3) + "]");
}

/*
  H2H Pin numbers
*/

// TODO replace all references of these with button and controller pins above

// Right to left (team A)
#define H2H_BUTTON_PIN_0 2
#define H2H_BUTTON_PIN_1 3
#define H2H_BUTTON_PIN_2 4
#define H2H_BUTTON_PIN_3 5
#define H2H_BUTTON_PIN_4 8
#define H2H_BUTTON_PIN_5 24
#define H2H_BUTTON_PIN_6 25
#define H2H_BUTTON_PIN_7 26

#define H2H_BUTTON_PIN_8 27
#define H2H_BUTTON_PIN_9 28
#define H2H_BUTTON_PIN_10 29
#define H2H_BUTTON_PIN_11 30
#define H2H_BUTTON_PIN_12 31
#define H2H_BUTTON_PIN_13 32
#define H2H_BUTTON_PIN_14 33
#define H2H_BUTTON_PIN_15 34

}  // namespace pins
}  // namespace kss
