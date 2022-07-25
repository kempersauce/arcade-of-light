#pragma once

/*
Game class
Where the magic happens
*/

#include "display/display.h"  // for kss::display::Display

class Game {
 public:
  kss::display::Display* display;

  Game(kss::display::Display* gameDisplay) { display = gameDisplay; }

  virtual void setup();
  virtual void loop();
};
