#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <vector>

#include "../examples/displays/five_strip.h"  // for FiveStripTest
#include "controls/button.h"                  // for Button
#include "controls/hardware/simple.h"         // for Simple context
#include "display/fast_led/five.h"            // for FiveDisplay
#include "serial/debug.h"                     // for Debug

using namespace kss;

display::fast_led::FiveDisplay* gameDisplay;
test::FiveStripTest* five_strip_test;

controls::hardware::Simple control_context;
std::vector<controls::Button*> buttons;

void setup() {
  Debug_init();
  gameDisplay = new display::fast_led::FiveDisplay();
  five_strip_test = new test::FiveStripTest(gameDisplay);
  five_strip_test->setup();
  for (uint8_t i = 0; i < 32; i++) {
    buttons.push_back(control_context.CreateButton(i));
  }
  // test->loop();
  gameDisplay->Show();
}

void loop() {
  for (size_t i = 0; i < gameDisplay->size.y; i++) {
    gameDisplay->Pixel(0, i) = CRGB::Red;
    gameDisplay->Pixel(1, i) = CRGB::Green;
    gameDisplay->Pixel(2, i) = CRGB::Blue;
    gameDisplay->Pixel(3, i) = CRGB::Yellow;
    gameDisplay->Pixel(4, i) = CRGB::Violet;
  }

  control_context.PollAll();

  for (size_t i = 0; i < buttons.size(); i++) {
    if (buttons[i]->IsDepressing()) {
      Debug("Button Pin: " + i);
    }
  }
  delay(100);
  five_strip_test->loop();
  gameDisplay->Show();
}
