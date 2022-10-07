#include <Arduino.h>
#include <FastLED.h>

#include "display/display.h"          // for Display
#include "display/fast_led/twenty.h"  // for TwentyDisplay
#include "games/game.h"               // for Game
#include "games/noise/noise.h"        // for NoiseGame
#include "pins/pin_setup.h"           // for pins::Init
#include "serial/debug.h"             // for Debug
#include "time/now.h"                 // for time::*

using namespace kss;

games::Game* game;
display::Display* gameDisplay;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();
  gameDisplay = (display::Display*)new display::fast_led::TwentyDisplay();

  game = (games::Game*)new games::noise::NoiseGame(gameDisplay);
  time::SetLoopTime();
  game->setup();
  gameDisplay->Show();
}

void loop() {
  time::SetLoopTime();
  game->loop();
  gameDisplay->Show();
}