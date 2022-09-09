#include <vector>  // for vector

#include "animation/fireworks_show.h"
#include "animation/noise.h"             // for NoiseAnimation
#include "display/display.h"             // for Display
#include "display/four_panel.h"          // for FourPanelDisplay
#include "engines/framerate.h"           // for FrameRate
#include "games/rhythm/rhythm_game.h"    // for RhythmGame
#include "games/rhythm/rhythm_single.h"  // for RhythmGameSingle
#include "serial/debug.h"                // for serial debugging

using namespace kss;

engines::FrameRate frameRate;

display::FourPanelDisplay* gameDisplay;
games::Game* game;

void setup() {
  // This only works if we're not using octo
  // FastLED.setBrightness(100);

  debug::Init();
  debug::println("Begin setup()");

  // Choose your Display type
  gameDisplay = new display::FourPanelDisplay();

  debug::println("gameDisplay created");

//   game = (games::Game*)new games::rhythm::RhythmGame(gameDisplay);
  game = (games::Game*)new games::rhythm::RhythmGameSingle(gameDisplay);

  debug::println("game created");

  game->setup();
  debug::println("game setup complete");

  debug::println("End setup()");

  // TODO should we show LEDs on setup?
  // gameDisplay->Show();
}

void loop() {
  //   debug::println("loop() entered");

  game->loop();

  //   debug::println("loop() Show Display");
  gameDisplay->Show();

  //   debug::println("loops brother");
  //frameRate.PrintFrameRate();

  delay(20);
}
