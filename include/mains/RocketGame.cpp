#include <Arduino.h>
#include <FastLED.h>

#include "controls/hardware/matrix.h"          // for Matrix
#include "display/display.h"                   // for Display
#include "display/h2h_octo.h"                  // for H2HDisplay
#include "display/instructo_panel_standard.h"  // for InstructoDisplay
#include "display/rocket.h"                    // for RocketDisplay
#include "engines/framerate.h"                 // for Framerate
#include "games/game.h"                        // for Game
#include "games/rocket/rocket_game.h"          // for RocketGame
#include "pins/pin_setup.h"                    // for pins::*
#include "serial/debug.h"                      // for Debug
#include "time/now.h"                          // for time::*

using namespace kss;

games::Game* game;
display::Display* gameDisplay;
display::Display* instructo_display;
controls::hardware::Matrix control_context;
engines::FrameRate framerate;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = new display::RocketDisplay();
  instructo_display = new display::InstructoDisplay(pins::Leds[12]);

  game = new games::rocket::RocketGame(
      gameDisplay, instructo_display,
      control_context.CreateButton(pins::Controllers[0], pins::Buttons[1]),
      control_context.CreateButton(pins::Controllers[0], pins::Buttons[0]));
  game->setup();
  Debug("Setup Complete");
}

void loop() {
  time::SetLoopTime();
  control_context.PollAll();
  game->loop();
  gameDisplay->Show();
  instructo_display->Show();
  framerate.PrintFrameRate();
}