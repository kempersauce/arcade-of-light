#include "animation/fireworks_show.h"    // for FireworksShow
#include "animation/noise.h"             // for NoiseAnimation
#include "audio/synth_sender.h"          // for SynthSender
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
games::Game* game;

controls::hardware::Matrix control_context;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  Debug("Begin setup()");

  // Choose your Display type
  gameDisplay = new display::octo::FourPanelDisplay();

  Debug("gameDisplay created");

  std::vector<controls::DirPad> dir_pads;

  for (size_t ctl_no = 0; ctl_no < pins::ControllerCount; ++ctl_no) {
    dir_pads.push_back(controls::RhythmController{control_context, ctl_no});
  }

  game = new games::rhythm::RhythmGame(gameDisplay, dir_pads);
  //   game = new games::rhythm::RhythmGameSingle(&gameDisplay->panels[0],
  //   dir_pads[0]);

  Debug("game created");

  game->setup();
  Debug("game setup complete");

  Debug("End setup()");

  // TODO should we show LEDs on setup?
  // gameDisplay->Show();
}

void loop() {
  time::SetLoopTime();

  control_context.PollAll();

  game->loop();

  //   Debug("Show Display");
  gameDisplay->Show();

  //   Debug("loops brother");
  //   frameRate.PrintFrameRate();

  //   delay(7);
}
