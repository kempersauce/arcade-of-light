
#include <Arduino.h>
#include <FastLED.h>

#include "controls/dir_pad.h"          // for DirPad
#include "controls/hardware/simple.h"  // for controls::hardware::Simple
#include "display/octo/twenty.h"       // for TwentyDisplay
#include "engines/framerate.h"         // for Framerate
#include "games/game.h"                // for Game
#include "games/life/beam_of_life.h"   // for BeamOfLife
#include "pins/pin_setup.h"            // for pins::*
#include "serial/debug.h"              // for Debug
#include "time/now.h"                  // for time::*

using namespace kss;

games::Game* game;
display::Display* gameDisplay;

constexpr uint8_t kFPS{8};
constexpr uint32_t kFrameDelayMillis{1000 / kFPS};

engines::FrameRate framerate;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = new display::octo::TwentyDisplay();

  game = (games::Game*)new games::life::BeamOfLife(gameDisplay);

  time::SetLoopTime();
  game->setup();
  gameDisplay->Show();
}

void loop() {
  time::SetLoopTime();
  game->loop();
  gameDisplay->Show();
  framerate.PrintFrameRate();
  delay(kFrameDelayMillis);
}