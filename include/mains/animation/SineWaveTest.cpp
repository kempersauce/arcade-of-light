#include <Arduino.h>
#include <FastLED.h>

#include "animation/sine_wave.h"       // for SineWave
#include "controls/h2h.h"              // for H2HController
#include "controls/hardware/matrix.h"  // for Matrix
#include "display/display.h"           // for Display
#include "display/h2h.h"               // for H2HDisplay
#include "engines/framerate.h"         // for FrameRate
#include "games/game.h"                // for Game
#include "pins/pin_setup.h"            // for pins::Init
#include "serial/debug.h"              // for Debug
#include "test/animation.h"            // for AnimationTest

using namespace kss;

engines::FrameRate frameRate;

games::Game* game;
display::Display* gameDisplay;
controls::hardware::Matrix control_context;

controls::H2HController controller;

animation::SineWave* sine_wave;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = new display::H2HDisplay();

  sine_wave = new animation::SineWave(CRGB::Cyan);
  sine_wave->waves.emplace_back(100, 0, .2);
  sine_wave->waves.emplace_back(100, 0, .1);
  sine_wave->waves.emplace_back(66, 0, .3);
  sine_wave->waves.emplace_back(66, 0, .4);
  sine_wave->waves.emplace_back(40, 0, .3);
  sine_wave->waves.emplace_back(40, 0, .5);
  sine_wave->waves.emplace_back(50, 0, .2);
  sine_wave->waves.emplace_back(50, 0, .1);

  game = new test::AnimationTest(gameDisplay, sine_wave);
  controller = controls::H2HController::TeamA(control_context);

  game->setup();
  Debug("End setup()");
}

void loop() {
  time::SetLoopTime();
  control_context.PollAll();

  // Do the waves with the buttons
  for (size_t i = 0; i < 8; ++i) {
    if (controller.buttons[i]->IsDepressing()) {
      sine_wave->waves[i].amplitude = 1;
    }
    if (controller.buttons[i]->IsReleasing()) {
      sine_wave->waves[i].amplitude = 0;
    }
  }

  game->loop();
  gameDisplay->Show();
  frameRate.PrintFrameRate();
}