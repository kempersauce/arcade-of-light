#include <vector>  // for vector

#include "animation/fireworks_show.h"    // for FireworksShow
#include "animation/noise.h"             // for NoiseAnimation
#include "display/display.h"             // for Display
#include "display/four_panel.h"          // for FourPanelDisplay
#include "engines/framerate.h"           // for FrameRate
#include "games/rhythm/rhythm_game.h"    // for RhythmGame
#include "games/rhythm/rhythm_single.h"  // for RhythmGameSingle
#include "pins/pin_setup.h"              // for pins::Init
#include "serial/debug.h"                // for serial debugging

using namespace kss;

engines::FrameRate frameRate;

display::FourPanelDisplay* gameDisplay;
games::Game* game;

void setup() {
  Debug_init();
  pins::Init();
  Debug("Begin setup()");

  // Choose your Display type
  gameDisplay = new display::FourPanelDisplay();

  Debug("gameDisplay created");

  game = (games::Game*)new games::rhythm::RhythmGame(gameDisplay);
    // game = (games::Game*)new games::rhythm::RhythmGameSingle(&gameDisplay->panels[0]);

  Debug("game created");

  game->setup();
  Debug("game setup complete");

  Debug("End setup()");

  // TODO should we show LEDs on setup?
  // gameDisplay->Show();
}

void loop() {
  //   Debug_here();

  game->loop();

  //   Debug("Show Display");
  gameDisplay->Show();

  //   Debug("loops brother");
  frameRate.PrintFrameRate();

  //   delay(7);
}
