#include <Arduino.h>
#include <FastLED.h>

#include <vector>  // for std::vector

#include "../examples/animation/animation.h"  // for AnimationTest
#include "animation/circle.h"                 // for Circle
#include "display/display.h"                  // for Display
#include "display/h2h.h"                      // for H2HDisplay
#include "engines/framerate.h"                // for FrameRate
#include "games/game.h"                       // for Game
#include "pins/pin_setup.h"                   // for pins::Init
#include "serial/debug.h"                     // for Debug
#include "time/now.h"                         // for time::*

using namespace kss;

engines::FrameRate frameRate;

games::Game* game;
display::Display* gameDisplay;
std::vector<animation::Animation*> animes;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  gameDisplay = new display::H2HDisplay();
  animation::Circle* circle;

  // 2" radius
  circle = new animation::Circle(2, CRGB::Red);
  circle->physics.location = {2, 7};
  animes.push_back(circle);

  circle = new animation::Circle(2, CRGB::Red);
  circle->physics.location = {2, 17.5};
  animes.push_back(circle);

  circle = new animation::Circle(2, CRGB::Red);
  circle->physics.location = {2.5, 27};
  animes.push_back(circle);

  circle = new animation::Circle(2, CRGB::Red);
  circle->physics.location = {2.5, 37.5};
  animes.push_back(circle);

  // 3" radius
  circle = new animation::Circle(3, CRGB::Red);
  circle->physics.location = {2, 57};
  circle->physics.velocity = {.2, 0};
  circle->physics.gravity = {0, -3};
  animes.push_back(circle);

  circle = new animation::Circle(3, CRGB::Red);
  circle->physics.location = {2, 77.5};
  animes.push_back(circle);

  circle = new animation::Circle(3, CRGB::Red);
  circle->physics.location = {2.5, 97};
  animes.push_back(circle);

  circle = new animation::Circle(3, CRGB::Red);
  circle->physics.location = {2.5, 137.5};
  animes.push_back(circle);

  game = new test::AnimationTest(gameDisplay, animes);
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