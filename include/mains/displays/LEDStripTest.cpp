#include <Arduino.h>
#include <FastLED.h>

#include "display/display.h"  // for Display
// #include "display/single.h"   // for SingleDisplay
#include "display/h2h_octo.h"  // for H2HDisplay
#include "pins/pin_setup.h"    // for LED_PIN_*
#include "serial/debug.h"      // for Debug

using namespace kss;

display::Display* gameDisplay;

void showColor(CRGB color) {
  for (size_t x = 0; x < gameDisplay->size.x; ++x) {
    for (size_t y = 0; y < gameDisplay->size.y; ++y) {
      gameDisplay->Pixel(x, y) = color;
      gameDisplay->Show();
      delay(10);
    }
  }
}

void setup() {
  Debug_init();
  // LED_PIN_12 (pin 30) is first pin on cable 4
  gameDisplay = (display::Display*)new display::H2HDisplay();

  Debug("End setup()");
}

void loop() {
  showColor(CRGB::Black);
  showColor(CRGB::Red);
  showColor(CRGB::Green);
  showColor(CRGB::Blue);
}