#pragma once

/*
Game class
Where the magic happens
*/

#include "display/display.h"  // for Display

namespace kss {
namespace games {

class Game {
 protected:
  display::Display& display;

 public:
  Game(display::Display& display) : display{display} {}

  virtual void setup();
  virtual void loop();
};

}  // namespace games
}  // namespace kss
