/*
Game class
Where the magic happens
*/

#pragma once

#include "animation/animation.h"  // for Animation

class Game {
 public:
  Display* display;

  Game(Display* gameDisplay) { display = gameDisplay; }

  virtual void setup();
  virtual void loop();
};
