#include <Arduino.h>
#include <FastLED.h>

#include "animation/sine_wave.h"       // for SineWave
#include "controls/h2h.h"              // for H2HController
#include "controls/hardware/matrix.h"  // for Matrix
#include "display/display.h"           // for Display
#include "display/h2h.h"               // for H2HDisplay
#include "display/octo/twenty.h"       // for TwentyDisplay
#include "engines/framerate.h"         // for FrameRate
#include "games/game.h"                // for Game
#include "pins/pin_setup.h"            // for pins::Init
#include "serial/debug.h"              // for Debug
#include "test/animation.h"            // for AnimationTest
#include "time/now.h"                  // for time::*

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

  display::octo::TwentyDisplay* disp = new display::octo::TwentyDisplay();
  gameDisplay = disp;

  const size_t display_width = disp->size.width;
  sine_wave = new animation::SineWave(CRGB::Cyan);
  sine_wave->waves.emplace_back(100, display_width / 4.0f, 0.1);
  sine_wave->waves.emplace_back(50, display_width / 8.0f, 0.1);
  sine_wave->waves.emplace_back(20, display_width / 8.0f, 0.1);
  sine_wave->waves.emplace_back(10, display_width / 12.0f, 0.05);
  sine_wave->waves.emplace_back(100, display_width / 4.0f, -0.1);
  sine_wave->waves.emplace_back(50, display_width / 8.0f, -0.1);
  sine_wave->waves.emplace_back(20, display_width / 8.0f, -0.1);
  sine_wave->waves.emplace_back(10, display_width / 12.0f, -0.05);

  game = new test::AnimationTest(disp, sine_wave);
  controller = controls::H2HController::TeamA(control_context);

  time::SetLoopTime();
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