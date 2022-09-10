
#include <Arduino.h>
#include <FastLED.h>

#include "controls/dir_pad.h"
#include "controls/hardware/simple.h"  // for controls::hardware::Simple
#include "display/five.h"              // for FiveDisplay
#include "games/game.h"                // for Game
#include "games/life/single_player.h"  // for LifeGameSinglePlayer

using namespace kss;

games::Game* game;
display::Display* gameDisplay;
controls::hardware::Simple control_context;

void setup() {
  gameDisplay = (display::Display*)new display::FiveDisplay();

  controls::DirPad dirPad{control_context.CreateButton(BUTTON_PIN_4),
                          control_context.CreateButton(BUTTON_PIN_3),
                          control_context.CreateButton(BUTTON_PIN_5),
                          control_context.CreateButton(BUTTON_PIN_2),
                          control_context.CreateButton(BUTTON_PIN_1),
                          control_context.CreateButton(BUTTON_PIN_0)};

  game =
      (games::Game*)new games::life::LifeGameSinglePlayer(gameDisplay, dirPad);
  game->setup();
  gameDisplay->Show();
}

void loop() {
  control_context.PollAll();
  game->loop();
  gameDisplay->Show();
}