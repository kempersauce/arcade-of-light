#include <Arduino.h>
#include <FastLED.h>

#include "controls/hardware/matrix.h"  // for Matrix
#include "display/display.h"           // for Display
#include "display/rocket.h"            // for RocketDisplay
#include "engines/framerate.h"         // for Framerate
#include "games/game.h"                // for Game
#include "games/rocket/rocket_game.h"  // for RocketGame
#include "pins/pin_setup.h"            // for pins::*
#include "serial/debug.h"              // for Debug

using namespace kss;

display::RocketDisplay* gameDisplay = new display::RocketDisplay();
controls::hardware::Matrix control_context;
games::rocket::RocketGame* game;
engines::FrameRate framerate;

void setup() {
  Debug_init();
  pins::Init();

  game = new games::rocket::RocketGame(
      gameDisplay,
      control_context.CreateButton(pins::Controllers[0], pins::Buttons[0]),
      control_context.CreateButton(pins::Controllers[0], pins::Buttons[1]));
  game->setup();
  Debug("Setup Complete");
}

void loop() {
  control_context.PollAll();
  game->loop();
  gameDisplay->Show();
  framerate.PrintFrameRate();
}