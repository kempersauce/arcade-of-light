#include <Arduino.h>
#include <FastLED.h>

#include <vector>  // for std::vector

#include "../examples/animation/animation.h"  // for AnimationTest
#include "animation/charge_bar.h"             // for Charge Barge
#include "display/display.h"                  // for Display
#include "display/h2h.h"                      // for H2HDisplay
#include "engines/framerate.h"                // for FrameRate
#include "games/game.h"                       // for Game
#include "pins/pin_setup.h"                   // for pins::Init
#include "serial/debug.h"                     // for Debug

using namespace kss;
int32_t heights[] = {0, 2, 4, 7, 10, 15, 32, 70, 150, 24};
int32_t numHeights = 10;
int32_t currentHeight = 0;

engines::FrameRate frameRate;

games::Game* game;
display::Display* gameDisplay;
animation::ChargeBar* chargeBar;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = new display::H2HDisplay();
  chargeBar = new animation::ChargeBar(CRGB::Red);

  game = new test::AnimationTest(gameDisplay, chargeBar);
  time::SetLoopTime();
  game->setup();
  Debug("End setup()");
}

void loop() {
  time::SetLoopTime();
  currentHeight++;
  if (currentHeight >= numHeights) {
    currentHeight = 0;
  }
  chargeBar->height = heights[currentHeight];
  game->loop();
  gameDisplay->Show();
  frameRate.PrintFrameRate();
  Debug(heights[currentHeight]);
  delay(1000);
}