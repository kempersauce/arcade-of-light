#include <Arduino.h>
#include <FastLED.h>

#include "controls/hardware/matrix.h"  // for Matrix
#include "display/h2h.h"               // for H2HDisplay
#include "engines/framerate.h"         // for Framerate
#include "games/rocket/rocket_game.h"  // for RocketGame
#include "pins/pin_setup.h"            // for pins::*
#include "serial/debug.h"              // for Debug
#include "time/now.h"                  // for time::*

using namespace kss;

games::rocket::RocketGame* game;
display::H2HDisplay* gameDisplay;
controls::hardware::Matrix control_context;
engines::FrameRate framerate;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = new display::H2HDisplay();

  game = new games::rocket::RocketGame(
      &gameDisplay->main_display, &gameDisplay->instructo_a,
      control_context.CreateButton(pins::Controllers[0], pins::Buttons[5]),
      control_context.CreateButton(pins::Controllers[0], pins::Buttons[4]));
  game->setup();
  Debug("Setup Complete");
}

void loop() {
  time::SetLoopTime();
  control_context.PollAll();
  game->loop();
  gameDisplay->Show();
  framerate.PrintFrameRate();
}