#pragma once

/*
Game class
Where the magic happens
*/

#include "display/display.h"  // for kss::display::Display

namespace kss {
namespace games {

class Game {
 public:
  kss::display::Display* display;

  Game(kss::display::Display* gameDisplay) { display = gameDisplay; }

  virtual void setup();
  virtual void loop();
};

}  // namespace games
}  // namespace kss
