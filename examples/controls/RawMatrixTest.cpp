
#include <Arduino.h>
#include <FastLED.h>

#include "pins/pin_setup.h"  // for pins::*
#include "serial/debug.h"    // for Debug

using namespace kss;

constexpr size_t controllerNum = sizeof(pins::Controllers);
constexpr size_t buttonNum = sizeof(pins::Buttons);

void setup() {
  Debug_init();
  pins::Init();

  digitalWrite(pins::Controllers[0], LOW);
  digitalWrite(pins::Controllers[1], HIGH);
  digitalWrite(pins::Controllers[2], HIGH);
  digitalWrite(pins::Controllers[3], HIGH);

  for (size_t button = 0; button < buttonNum; button++) {
    if (digitalRead(pins::Buttons[button]) == HIGH) {
      Debug("button " + button + " reporting for duty");
    }
  }
}

void loop() {
  for (size_t controller = 0; controller < controllerNum; controller++) {
    digitalWrite(pins::Controllers[controller], LOW);
    // Allow the signal to settle before polling
    delayMicroseconds(5);

    for (size_t button = 0; button < buttonNum; button++) {
      if (digitalRead(pins::Buttons[button]) == LOW) {
        Debug("controller=" + controller + " button=" + button);
      }
    }
    digitalWrite(pins::Controllers[controller], HIGH);
  }
}