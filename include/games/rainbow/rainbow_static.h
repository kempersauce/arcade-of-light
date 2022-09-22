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

  void loop(const uint32_t now = millis()) override { background.draw(display); }
};

}  // namespace rainbow
}  // namespace games
}  // namespace kss
