#include <Arduino.h>
#include <FastLED.h>

#include "controls/hardware/simple.h"  // for controls::hardware::Simple
#include "display/display.h"           // for Display
#include "display/h2h.h"               // for H2HDisplay
#include "display/rocket.h"            // for RocketDisplay
#include "games/game.h"                // for Game
#include "games/rocket/rocket_game.h"  // for RocketGame
#include "pins/pin_setup.h"            // for pins::*
#include "serial/debug.h"              // for Debug

using namespace kss;

display::RocketDisplay* gameDisplay = new display::RocketDisplay();
controls::hardware::Simple control_context;
games::rocket::RocketGame* game;

void setup() {
  Debug_init();
  pins::Init();

  game = new games::rocket::RocketGame(
      gameDisplay, control_context.CreateButton(pins::Buttons[0]),
      control_context.CreateButton(pins::Buttons[1]));
  game->setup();
}

void loop() {
  control_context.PollAll();
  game->loop();
  gameDisplay->Show();
}