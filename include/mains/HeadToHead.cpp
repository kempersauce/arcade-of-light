#include <Arduino.h>
#include <FastLED.h>

#include "controls/h2h.h"               // for H2HController
#include "controls/hardware/matrix.h"   // for Matrix
#include "display/h2h.h"                // for H2HDisplay
#include "engines/framerate.h"          // for Framerate
#include "games/head2head/head2head.h"  // for Head2Head
#include "pins/pin_setup.h"             // for pins::Init
#include "time/now.h"                   // for time::*

using namespace kss;

games::h2h::Head2Head* game;
display::H2HDisplay* gameDisplay;
controls::hardware::Matrix control_context;
engines::FrameRate framerate;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = new display::H2HDisplay();

  controls::H2HController teamA{
      controls::H2HController::TeamA(control_context)};
  controls::H2HController teamB{
      controls::H2HController::TeamB(control_context)};

  game = new games::h2h::Head2Head(&gameDisplay->main_display,
                                   &gameDisplay->instructo_a,
                                   &gameDisplay->instructo_b, teamA, teamB);
  game->setup();
  gameDisplay->Show();
  Debug("Setup Complete");
}

void loop() {
  time::SetLoopTime();
  control_context.PollAll();
  game->loop();
  gameDisplay->Show();
  framerate.PrintFrameRate();
}