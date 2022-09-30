
#include <Arduino.h>
#include <FastLED.h>

#include "controls/h2h_controller.h"    // for H2HController
#include "controls/hardware/matrix.h"   // for Matrix
#include "display/display.h"            // for Display
#include "display/h2h_octo.h"           // for H2HDisplay
#include "engines/framerate.h"          // for Framerate
#include "games/game.h"                 // for Game
#include "games/head2head/head2head.h"  // for Head2Head
#include "pins/pin_setup.h"             // for pins::Init
#include "time/now.h"                   // for SetLoopTime

using namespace kss;

games::Game* game;
display::Display* gameDisplay;
controls::hardware::Matrix control_context;
engines::FrameRate framerate;

void setup() {
  Debug_init();
  pins::Init();
  gameDisplay = new display::H2HDisplay();

  controls::H2HController teamA;
  teamA.buttons[0] =
      control_context.CreateButton(pins::Controllers[0], pins::Buttons[5]);
  teamA.buttons[1] =
      control_context.CreateButton(pins::Controllers[0], pins::Buttons[4]);
  teamA.buttons[2] =
      control_context.CreateButton(pins::Controllers[0], pins::Buttons[3]);
  teamA.buttons[3] =
      control_context.CreateButton(pins::Controllers[0], pins::Buttons[2]);

  teamA.buttons[4] =
      control_context.CreateButton(pins::Controllers[1], pins::Buttons[5]);
  teamA.buttons[5] =
      control_context.CreateButton(pins::Controllers[1], pins::Buttons[4]);
  teamA.buttons[6] =
      control_context.CreateButton(pins::Controllers[1], pins::Buttons[3]);
  teamA.buttons[7] =
      control_context.CreateButton(pins::Controllers[1], pins::Buttons[2]);

  controls::H2HController teamB;
  teamB.buttons[0] =
      control_context.CreateButton(pins::Controllers[3], pins::Buttons[2]);
  teamB.buttons[1] =
      control_context.CreateButton(pins::Controllers[3], pins::Buttons[3]);
  teamB.buttons[2] =
      control_context.CreateButton(pins::Controllers[3], pins::Buttons[4]);
  teamB.buttons[3] =
      control_context.CreateButton(pins::Controllers[3], pins::Buttons[5]);

  teamB.buttons[4] =
      control_context.CreateButton(pins::Controllers[2], pins::Buttons[2]);
  teamB.buttons[5] =
      control_context.CreateButton(pins::Controllers[2], pins::Buttons[3]);
  teamB.buttons[6] =
      control_context.CreateButton(pins::Controllers[2], pins::Buttons[4]);
  teamB.buttons[7] =
      control_context.CreateButton(pins::Controllers[2], pins::Buttons[5]);

  game = new games::h2h::Head2Head(gameDisplay, teamA, teamB);
  game->setup();
  gameDisplay->Show();
  Debug("Setup Complete");
}

void loop() {
  time::SetLoopTime();
  control_context.PollAll();
  game->loop();
  gameDisplay->Show();
  //   framerate.PrintFrameRate();
}