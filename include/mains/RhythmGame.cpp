#include <vector>  // for std::vector

#include "controls/hardware/matrix.h"    // for Matrix
#include "controls/rhythm.h"             // for RhythmController
#include "display/display.h"             // for Display
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

display::octo::FourPanelDisplay* gameDisplay;
games::rhythm::RhythmGame* game;

controls::hardware::Matrix control_context;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  Debug("Begin setup()");

  // Invert color scheme on dip switch 3
  if (pins::ReadDip(3)) {
    Debug("Inverting player color scheme");
    for (size_t i = 0; i < 4; ++i) {
      std::swap(games::rhythm::kPlayerHues[i],
                games::rhythm::kPlayerOffhues[i]);
    }
  }

  // Choose your Display type
  gameDisplay = new display::octo::FourPanelDisplay();

  Debug("gameDisplay created");

  std::vector<controls::RhythmController> dir_pads;

  for (size_t ctl_no = 0; ctl_no < pins::ControllerCount; ++ctl_no) {
    dir_pads.emplace_back(control_context, ctl_no);
  }

  game = new games::rhythm::RhythmGame(gameDisplay, dir_pads);

  Debug("game created");

  time::SetLoopTime();
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
