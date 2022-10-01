#include <Arduino.h>
#include <FastLED.h>

#include "controls/hardware/matrix.h"      // for Matrix
#include "display/display.h"               // for Display
#include "display/h2h.h"                   // for H2HDisplay
#include "display/octo/instructo_panel.h"  // for InstructoDisplay
#include "display/rocket.h"                // for RocketDisplay
#include "engines/framerate.h"             // for Framerate
#include "games/game.h"                    // for Game
#include "games/rocket/rocket_game.h"      // for RocketGame
#include "pins/pin_setup.h"                // for pins::*
#include "serial/debug.h"                  // for Debug
#include "time/now.h"                      // for time::*

using namespace kss;

games::Game* game;
display::Display* gameDisplay;
display::Display* instructo_display = NULL;
controls::hardware::Matrix control_context;
engines::FrameRate framerate;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = new display::RocketDisplay();
  instructo_display = new display::octo::InstructoDisplay(pins::Leds[12]);

  game = new games::rocket::RocketGame(
      gameDisplay, instructo_display,
      control_context.CreateButton(pins::Controllers[0], pins::Buttons[1]),
      control_context.CreateButton(pins::Controllers[0], pins::Buttons[0]));
  game->setup();
  Debug("Setup Complete");
}

void loop() {
  Debug("Setting loop time");
  delay(10);
  time::SetLoopTime();
  Debug("Polling buttons");
  delay(10);
  control_context.PollAll();
  Debug("Looping game");
  delay(10);
  game->loop();
  Debug("Showing game display");
  delay(10);
  gameDisplay->Show();
  Debug("Showing instructo display");
  delay(10);
  instructo_display->Show();
  framerate.PrintFrameRate();
}