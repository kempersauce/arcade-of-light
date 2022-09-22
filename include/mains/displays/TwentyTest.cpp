#include <Arduino.h>
#include <FastLED.h>

#include "display/display.h"    // for Display
#include "display/twenty_standard.h"     // for TwentyStandardDisplay
#include "games/game.h"         // for Game
#include "games/noise/noise.h"  // for NoiseGame

using namespace kss;

games::Game* game;
display::Display* gameDisplay;

void setup() {
  gameDisplay = (display::Display*)new display::TwentyDisplayStandard();

  game = (games::Game*)new games::noise::NoiseGame(gameDisplay);
  game->setup();
  gameDisplay->Show();
}

void loop() {
  game->loop();
  gameDisplay->Show();
}