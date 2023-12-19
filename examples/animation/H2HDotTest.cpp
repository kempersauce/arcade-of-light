#include <Arduino.h>
#include <FastLED.h>

#include <vector>  // for std::vector

#include "../examples/animation/animation.h"  // for AnimationTest
#include "display/display.h"                  // for Display
#include "display/h2h.h"                      // for H2HDisplay
#include "engines/framerate.h"                // for FrameRate
#include "games/game.h"                       // for Game
#include "games/head2head/dot.h"              // for H2HDot
#include "math/random.h"                      // for random::*
#include "pins/pin_setup.h"                   // for pins::Init
#include "serial/debug.h"                     // for Debug
#include "time/now.h"                         // for time::*

using namespace kss;
using namespace games::h2h;

engines::FrameRate frameRate;

games::Game* game;
display::H2HDisplay* gameDisplay;
std::vector<animation::Animation*> animes;

H2HDot* MakeDot(uint8_t strip_index, CRGB fast_color) {
  H2HDot* dot = new H2HDot(CRGB::White, fast_color);
  dot->DropAt({strip_index, math::random::Int8()});
  dot->physics.velocity.y *= 2.5;
  dot->physics.LocationMax = gameDisplay->main_display.size.height;
  dot->physics.BounceFactor = -1.0;  // perfect bounce
  dot->physics.ExplodeVelocity = 100000;

  return dot;
}

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = new display::H2HDisplay();

  uint8_t strip_index = 0;
  animes.push_back(MakeDot(strip_index++, CRGB::Purple));
  animes.push_back(MakeDot(strip_index++, CRGB::Cyan));
  animes.push_back(MakeDot(strip_index++, CRGB::Purple));
  animes.push_back(MakeDot(strip_index++, CRGB::Cyan));
  animes.push_back(MakeDot(strip_index++, CRGB::Purple));
  animes.push_back(MakeDot(strip_index++, CRGB::Cyan));
  animes.push_back(MakeDot(strip_index++, CRGB::Purple));
  animes.push_back(MakeDot(strip_index++, CRGB::Cyan));

  game = new test::AnimationTest(&gameDisplay->main_display, animes);
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