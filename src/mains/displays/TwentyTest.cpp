#include <Arduino.h>
#include <FastLED.h>

#include "display/display.h"          // for Display
#include "display/octo/four_panel.h"  // for FourPanelDisplay
#include "games/game.h"               // for Game
#include "games/noise/noise.h"        // for NoiseGame
#include "pins/pin_setup.h"           // for pins::Init
#include "serial/debug.h"             // for Debug
#include "test/animation.h"           // for AnimationTest
#include "test/multi_game.h"          // for MultiGameTest
#include "time/now.h"                 // for time::*

using namespace kss;

games::Game* game;
display::octo::TwentyDisplay* gameDisplay;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = new display::octo::TwentyDisplay();

  animation::NoiseAnimation noise{gameDisplay->size};
  game = (games::Game*)new test::AnimationTest(gameDisplay, &noise);
  time::SetLoopTime();
  game->setup();
}

void loop() {
  time::SetLoopTime();
  game->loop();
  gameDisplay->Show();
}