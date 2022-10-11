#include <Arduino.h>
#include <FastLED.h>

#include <vector>  // for std::vector

#include "animation/wave_out.h"   // for WaveOut
#include "display/display.h"      // for Display
#include "display/h2h.h"          // for H2HDisplay
#include "engines/framerate.h"    // for FrameRate
#include "games/game.h"           // for Game
#include "games/head2head/dot.h"  // for H2HDot
#include "math/random.h"          // for random::*
#include "pins/pin_setup.h"       // for pins::Init
#include "serial/debug.h"         // for Debug
#include "test/animation.h"       // for AnimationTest
#include "time/now.h"             // for time::*

using namespace kss;
using namespace games::h2h;

engines::FrameRate frameRate;

games::Game* game;
display::H2HDisplay* gameDisplay;
animation::WaveOut* anime;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = new display::H2HDisplay();
  const auto size = gameDisplay->main_display.size;
  anime = new animation::WaveOut(200, 255);
//   anime->AddSquareSource(0, (size.height - 1) / 2.0f);
//   anime->AddSource({size.width + 10, (size.height - 1) / 2.0f});

  anime->AddSource({(size.width - 1) / 2.0f, (size.height - 1) * 2.0f / 3.0f});
//   anime->AddSource({(size.width - 1) / 2.0f, (size.height - 1) / 3.0f});
  anime->wave.wavelength = size.height / 27.0f;

  game = new test::AnimationTest(&gameDisplay->main_display, anime);
  time::SetLoopTime();
  game->setup();
  Debug("End setup()");
}

void loop() {
  time::SetLoopTime();
  game->loop();
  gameDisplay->Show();
  frameRate.PrintFrameRate();
}