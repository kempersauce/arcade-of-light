#pragma once

/*
Game class
Where the magic happens
*/

#include "display/display.h"  // for Display

class Game {
 public:
  Display* display;

  Game(Display* gameDisplay) { display = gameDisplay; }

  virtual void setup();
  virtual void loop();
};
