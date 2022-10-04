#include <Arduino.h>
#include <FastLED.h>

#include <vector>  // for std::vector

#include "animation/diamond.h"  // for Diamond
#include "display/display.h"    // for Display
#include "display/h2h_octo.h"   // for H2HDisplay
#include "engines/framerate.h"  // for FrameRate
#include "games/game.h"         // for Game
#include "pins/pin_setup.h"     // for pins::Init
#include "serial/debug.h"       // for Debug
#include "test/animation.h"     // for AnimationTest

using namespace kss;

engines::FrameRate frameRate;

games::Game* game;
display::Display* gameDisplay;
animation::Diamond* diamond;


void setup() {
  Debug_init();
  pins::Init();

  gameDisplay = new display::H2HDisplay();
  diamond = new animation::Diamond(4, 25, 10, 5, CRGB::Red);

  game = new test::AnimationTest(gameDisplay, diamond);
  game->setup();
  Debug("End setup()");
}

void loop() {
  game->loop();
  gameDisplay->Show();
  frameRate.PrintFrameRate();
}