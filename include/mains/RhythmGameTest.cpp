#include "controls/hardware/matrix.h"    // for Matrix
#include "controls/rhythm.h"             // for RhythmController
#include "display/display.h"             // for Display
#include "display/h2h_5_test.h"          // for H2H5TestDisplay
#include "display/octo/four_panel.h"     // for FourPanelDisplay
#include "engines/framerate.h"           // for FrameRate
#include "games/rhythm/rhythm_game.h"    // for RhythmGame
#include "games/rhythm/rhythm_single.h"  // for RhythmGameSingle
#include "pins/pin_setup.h"              // for pins::Init
#include "serial/debug.h"                // for serial debugging
#include "serial/hw_serials.h"           // for kHwSerials
#include "time/now.h"                    // for time::*

using namespace kss;

engines::FrameRate frameRate;

display::Display* gameDisplay;
games::rhythm::RhythmGameSingle* game;

controls::hardware::Matrix control_context;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  Debug("Begin setup()");

  // Choose your Display type
  display::H2H5TestDisplay* disp = new display::H2H5TestDisplay();
  gameDisplay = disp;

  Debug("gameDisplay created");

  controls::RhythmController dir_pad{control_context, 0};

  game = new games::rhythm::RhythmGameSingle(&disp->main_display, dir_pad, 0);

  Debug("game created");

  game->setup();

  Debug("End setup()");
}

void loop() {
  time::SetLoopTime();
  control_context.PollAll();
  game->loop();
  gameDisplay->Show();
  frameRate.PrintFrameRate();
}
