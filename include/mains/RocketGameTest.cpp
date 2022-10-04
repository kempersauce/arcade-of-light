#include <Arduino.h>
#include <FastLED.h>

#include "controls/hardware/matrix.h"  // for Matrix
#include "controls/rocket.h"           // for RocketController
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

  controls::RocketController controller{
      controls::RocketController::CreateTest(control_context, 0)};

  game = new games::rocket::RocketGame(&gameDisplay->main_display,
                                       &gameDisplay->instructo_a, controller);

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