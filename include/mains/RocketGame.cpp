#include <Arduino.h>
#include <FastLED.h>

#include "controls/hardware/matrix.h"  // for Matrix
#include "controls/rocket.h"           // for RocketController
#include "display/rocket.h"            // for RocketDisplay
#include "engines/framerate.h"         // for Framerate
#include "games/rocket/rocket_game.h"  // for RocketGame
#include "pins/pin_setup.h"            // for pins::*
#include "serial/debug.h"              // for Debug
#include "time/now.h"                  // for time::*

using namespace kss;

games::rocket::RocketGame* game;
display::RocketDisplay* gameDisplay;
controls::hardware::Matrix control_context;
engines::FrameRate framerate;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = new display::RocketDisplay();
  controls::RocketController controller{control_context};

  game = new games::rocket::RocketGame(&gameDisplay->main_display,
                                       &gameDisplay->instructo, controller);

  time::SetLoopTime();
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