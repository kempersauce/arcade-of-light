
#include <Arduino.h>
#include <FastLED.h>

#include "controls/h2h_controller.h"    // for H2HController
#include "controls/hardware/simple.h"   // for Simple context
#include "display/display.h"            // for Display
#include "display/h2h.h"                // for H2HDisplay
#include "games/game.h"                 // for Game
#include "games/head2head/head2head.h"  // for Head2Head

using namespace kss;

games::Game* game;
display::Display* gameDisplay;
controls::hardware::Simple control_context;

void setup() {
  gameDisplay = (display::Display*)new display::H2HDisplay();

  controls::H2HController teamA;
  teamA.buttons[0] = control_context.CreateButton(H2H_BUTTON_PIN_7);
  teamA.buttons[1] = control_context.CreateButton(H2H_BUTTON_PIN_6);
  teamA.buttons[2] = control_context.CreateButton(H2H_BUTTON_PIN_5);
  teamA.buttons[3] = control_context.CreateButton(H2H_BUTTON_PIN_4);
  teamA.buttons[4] = control_context.CreateButton(H2H_BUTTON_PIN_3);
  teamA.buttons[5] = control_context.CreateButton(H2H_BUTTON_PIN_2);
  teamA.buttons[6] = control_context.CreateButton(H2H_BUTTON_PIN_1);
  teamA.buttons[7] = control_context.CreateButton(H2H_BUTTON_PIN_0);

  controls::H2HController teamB;
  teamB.buttons[0] = control_context.CreateButton(H2H_BUTTON_PIN_8);
  teamB.buttons[1] = control_context.CreateButton(H2H_BUTTON_PIN_9);
  teamB.buttons[2] = control_context.CreateButton(H2H_BUTTON_PIN_10);
  teamB.buttons[3] = control_context.CreateButton(H2H_BUTTON_PIN_11);
  teamB.buttons[4] = control_context.CreateButton(H2H_BUTTON_PIN_12);
  teamB.buttons[5] = control_context.CreateButton(H2H_BUTTON_PIN_13);
  teamB.buttons[6] = control_context.CreateButton(H2H_BUTTON_PIN_14);
  teamB.buttons[7] = control_context.CreateButton(H2H_BUTTON_PIN_15);

  game = (games::Game*)new games::h2h::Head2Head(gameDisplay, teamA, teamB);
  game->setup();
  gameDisplay->Show();
}

void loop() {
  control_context.PollAll();
  game->loop();
  gameDisplay->Show();
}