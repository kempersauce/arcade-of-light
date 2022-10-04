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

  display::H2HDisplay* disp = new display::H2HDisplay();
  gameDisplay = disp;

  sine_wave = new animation::SineWave(CRGB::Cyan);
  sine_wave->waves.emplace_back(100, 1, .2);
  sine_wave->waves.emplace_back(100, 1, .1);
  sine_wave->waves.emplace_back(66, 1, .3);
  sine_wave->waves.emplace_back(66, 1, .4);
  sine_wave->waves.emplace_back(40, 1, .3);
  sine_wave->waves.emplace_back(40, 1, .5);
  sine_wave->waves.emplace_back(50, 1, .2);
  sine_wave->waves.emplace_back(50, 1, .1);

  game = new test::AnimationTest(&disp->main_display, sine_wave);
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
      sine_wave->waves[i].On();
    }
    if (controller.buttons[i]->IsReleasing()) {
      sine_wave->waves[i].Off();
    }
  }

  game->loop();
  gameDisplay->Show();
  frameRate.PrintFrameRate();
}