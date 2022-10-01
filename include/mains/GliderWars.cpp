
#include <Arduino.h>
#include <FastLED.h>

#include "controls/h2h_controller.h"   // for H2HController
#include "controls/hardware/simple.h"  // for Simple
#include "display/display.h"           // for Display
#include "display/octo/h2h.h"          // for H2HDisplay
#include "games/game.h"                // for Game
#include "games/life/glider_wars.h"    // for GliderWars

using namespace kss;

games::Game* game;
display::Display* gameDisplay;
controls::hardware::Simple control_context;

void setup() {
  gameDisplay = (display::Display*)new display::H2HDisplay();

  controls::H2HController teamA;
  teamA.buttons[0] = control_context.CreateButton(H2H_BUTTON_PIN_7);
  teamA.buttons[7] = control_context.CreateButton(H2H_BUTTON_PIN_0);

  controls::H2HController teamB;
  teamB.buttons[0] = control_context.CreateButton(H2H_BUTTON_PIN_8);
  teamB.buttons[7] = control_context.CreateButton(H2H_BUTTON_PIN_15);

  game = (games::Game*)new games::life::GliderWarsGame(
      gameDisplay, teamA.buttons[0], teamB.buttons[0], teamA.buttons[7],
      teamB.buttons[7]);
  game->setup();
  gameDisplay->Show();
}

void loop() {
  control_context.PollAll();
  game->loop();
  gameDisplay->Show();
}