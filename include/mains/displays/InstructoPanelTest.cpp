#include <Arduino.h>
#include <FastLED.h>

#include "display/display.h"                   // for Display
#include "display/fast_led/instructo_panel.h"  // for InstructoDisplay
#include "engines/framerate.h"                 // for FrameRate
#include "games/game.h"                        // for Game
#include "games/rainbow/rainbow.h"             // for RainbowGame
#include "pins/pin_setup.h"                    // for LED_PIN_*
#include "serial/debug.h"                      // for Debug
#include "time/now.h"                          // for time::*

using namespace kss;

engines::FrameRate frameRate;

games::Game* game;
display::Display* gameDisplay;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = (display::Display*)new display::fast_led::InstructoDisplay();

  game = (games::Game*)new games::rainbow::RainbowGame(gameDisplay);
  time::SetLoopTime();
  game->setup();
  Debug("End setup()");
}

void loop() {
  time::SetLoopTime();
  game->loop();
  gameDisplay->Show();
  frameRate.PrintFrameRate();
}