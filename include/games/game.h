#pragma once

/*
Game class
Where the magic happens
*/

#include "display/display.h"  // for Display
#include "serial/debug.h"     // for Debug

namespace kss {
namespace games {

class Game {
 protected:
  display::Display* const display;

 public:
  Game(display::Display* display) : display{display} {}
  virtual ~Game() = default;

  virtual void setup() = 0;
  virtual void loop(const uint32_t now = millis()) = 0;
};

}  // namespace games
}  // namespace kss
