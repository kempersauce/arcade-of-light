#include <Arduino.h>
#include <FastLED.h>

#include "PinSetup.h"                 // for LED_PIN_*
#include "display/display.h"          // for Display
#include "display/instructo_panel.h"  // for InstructoDisplay
#include "engines/framerate.h"        // for FrameRate
#include "games/game.h"               // for Game
#include "games/rainbow/rainbow.h"    // for RainbowGame
#include "serial/debug.h"             // for Debug

using namespace kss;

engines::FrameRate frameRate;

games::Game* game;
display::Display* gameDisplay;

void setup() {
  Debug_init();
  // LED_PIN_12 (pin 30) is first pin on cable 4
  gameDisplay = (display::Display*)new display::InstructoDisplay(LED_PIN_12);

  game = (games::Game*)new games::rainbow::RainbowGame(gameDisplay);
  game->setup();
  Debug("End setup()");
}

void loop() {
  game->loop();
  gameDisplay->Show();
  frameRate.PrintFrameRate();
}