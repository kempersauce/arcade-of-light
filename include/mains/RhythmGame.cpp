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
audio::SynthSender* synths[4];

void setup() {
  Debug_init();
  pins::Init();
  Debug("Begin setup()");

  // Choose your Display type
  gameDisplay = new display::FourPanelDisplay();

  Debug("gameDisplay created");

  game = (games::Game*)new games::rhythm::RhythmGame(gameDisplay);
  //   game = (games::Game*)new
  //   games::rhythm::RhythmGameSingle(&gameDisplay->panels[0]);

  for (size_t i = 0; i < 4; ++i) {
    synths[i] = new audio::SynthSender(
        control_context.CreateButton(pins::Controllers[i], pins::Buttons[0]),
        control_context.CreateButton(pins::Controllers[i], pins::Buttons[1]),
        control_context.CreateButton(pins::Controllers[i], pins::Buttons[2]),
        control_context.CreateButton(pins::Controllers[i], pins::Buttons[3]),
        control_context.CreateButton(pins::Controllers[i], pins::Buttons[4]),
        control_context.CreateButton(pins::Controllers[i], pins::Buttons[5]),
        serial::kHwSerials[i]);
  }

  Debug("game created");

  game->setup();
  Debug("game setup complete");

  Debug("End setup()");

  // TODO should we show LEDs on setup?
  // gameDisplay->Show();
}

void loop() {
  //   Debug_here();
  control_context.PollAll();
  //   Debug("Poll'd");
  for (auto synth : synths) {
    synth->checkButtonChange();
  }

  game->loop();

  //   Debug("Show Display");
  gameDisplay->Show();

  //   Debug("loops brother");
  frameRate.PrintFrameRate();

  //   delay(7);
}
