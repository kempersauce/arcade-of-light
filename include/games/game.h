#pragma once

/*
Game class
Where the magic happens
*/

#include "display/display.h"  // for Display

namespace kss {
namespace games {

class Game {
 public:
  display::Display* display;

  Game(display::Display* gameDisplay) { display = gameDisplay; }

  virtual void setup();
  virtual void loop();
};

}  // namespace games
}  // namespace kss
