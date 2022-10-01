#include <Arduino.h>
#include <FastLED.h>

#include "animation/sine_wave.h"  // for SineWave
#include "display/display.h"      // for Display
#include "display/h2h_octo.h"     // for H2HDisplay
#include "engines/framerate.h"    // for FrameRate
#include "games/game.h"           // for Game
#include "pins/pin_setup.h"       // for pins::Init
#include "serial/debug.h"         // for Debug
#include "test/animation.h"       // for AnimationTest

using namespace kss;

engines::FrameRate frameRate;

games::Game* game;
display::Display* gameDisplay;
animation::SineWave* sine_wave;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = new display::H2HDisplay();

  sine_wave = new animation::SineWave(CRGB::Cyan);

  game = new test::AnimationTest(gameDisplay, sine_wave);
  game->setup();
  Debug("End setup()");
}

void loop() {
  time::SetLoopTime();
  game->loop();
  gameDisplay->Show();
  frameRate.PrintFrameRate();
}