#pragma once

#include "animation/rainbow.h"  // for Rainbow
#include "display/display.h"    // for Display
#include "games/game.h"         // for Game

namespace kss {
namespace games {
namespace rainbow {

class RainbowStatic : public Game {
  animation::Rainbow background;

 public:
  RainbowStatic(display::Display* gameDisplay) : Game(gameDisplay) {}

  virtual void setup() override {}

  virtual void loop() override { background.draw(display); }
};

}  // namespace rainbow
}  // namespace games
}  // namespace kss
