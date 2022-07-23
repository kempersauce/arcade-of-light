/*
Game class
Where the magic happens
*/

#pragma once

#include <Animation.h>

class Game {
 public:
  Display* display;

  Game(Display* gameDisplay) { display = gameDisplay; }

  virtual void setup();
  virtual void loop();
};
