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

  void setup() override {}

  void loop() override { background.Draw(display); }
};

}  // namespace rainbow
}  // namespace games
}  // namespace kss
