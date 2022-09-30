#include <Arduino.h>
#include <FastLED.h>

#include <vector>  // for std::vector

#include "animation/circle.h"   // for Circle
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
std::vector<animation::Animation*> animes;

void setup() {
  Debug_init();
  pins::Init();

  gameDisplay = new display::H2HDisplay();
  animation::Circle* circle;

  // 1" radius
  circle = new animation::Circle(1, CRGB::Red);
  circle->physics.location = {2, 7};
  animes.push_back(circle);

  circle = new animation::Circle(1, CRGB::Red);
  circle->physics.location = {2, 17.5};
  animes.push_back(circle);

  circle = new animation::Circle(1, CRGB::Red);
  circle->physics.location = {2.5, 27};
  animes.push_back(circle);

  circle = new animation::Circle(1, CRGB::Red);
  circle->physics.location = {2.5, 37.5};
  animes.push_back(circle);

  // 3" radius
  circle = new animation::Circle(3, CRGB::Red);
  circle->physics.location = {2, 7};
  animes.push_back(circle);

  circle = new animation::Circle(3, CRGB::Red);
  circle->physics.location = {2, 17.5};
  animes.push_back(circle);

  circle = new animation::Circle(3, CRGB::Red);
  circle->physics.location = {2.5, 27};
  animes.push_back(circle);

  circle = new animation::Circle(3, CRGB::Red);
  circle->physics.location = {2.5, 37.5};
  animes.push_back(circle);

  game = new test::AnimationTest(gameDisplay, animes);
  game->setup();
  Debug("End setup()");
}

void loop() {
  game->loop();
  gameDisplay->Show();
  frameRate.PrintFrameRate();
}