#include "animation/fireworks_show.h"    // for FireworksShow
#include "animation/noise.h"             // for NoiseAnimation
#include "audio/synth_sender.h"          // for SynthSender
#include "controls/hardware/matrix.h"    // for Matrix
#include "display/display.h"             // for Display
#include "display/four_panel.h"          // for FourPanelDisplay
#include "engines/framerate.h"           // for FrameRate
#include "games/rhythm/rhythm_game.h"    // for RhythmGame
#include "games/rhythm/rhythm_single.h"  // for RhythmGameSingle
#include "pins/pin_setup.h"              // for pins::Init
#include "serial/debug.h"                // for serial debugging
#include "serial/hw_serials.h"           // for kHwSerials

using namespace kss;

engines::FrameRate frameRate;

display::FourPanelDisplay* gameDisplay;
games::Game* game;

controls::hardware::Matrix control_context;

void setup() {
  Debug_init();
  pins::Init();
  time::SetLoopTime();
  Debug("Begin setup()");

  // Choose your Display type
  gameDisplay = new display::FourPanelDisplay();

  Debug("gameDisplay created");

  std::vector<controls::DirPad> dir_pads;

  for (uint8_t controller_pin : pins::Controllers) {
    dir_pads.emplace_back(
        control_context.CreateButton(controller_pin, pins::Buttons[5]),
        control_context.CreateButton(controller_pin, pins::Buttons[4]),
        control_context.CreateButton(controller_pin, pins::Buttons[3]),
        control_context.CreateButton(controller_pin, pins::Buttons[2]),
        control_context.CreateButton(controller_pin, pins::Buttons[1]),
        control_context.CreateButton(controller_pin, pins::Buttons[0]));
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
