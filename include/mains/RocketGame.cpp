#include <Arduino.h>
#include <FastLED.h>

#include "controls/hardware/simple.h"  // for controls::hardware::Simple
#include "display/display.h"           // for Display
#include "display/h2h.h"               // for H2HDisplay
#include "display/rocket.h"            // for RocketDisplay
#include "games/game.h"                // for Game
#include "games/rocket/rocket_game.h"  // for RocketGame

using namespace kss;

display::RocketDisplay* gameDisplay = new display::RocketDisplay();
controls::hardware::Simple control_context;
games::rocket::RocketGame* game = new games::rocket::RocketGame(
    gameDisplay, control_context.CreateButton(BUTTON_PIN_0),
    control_context.CreateButton(BUTTON_PIN_1));

void setup() { game->setup(); }

void loop() {
  control_context.PollAll();
  game->loop();
  gameDisplay->Show();
}