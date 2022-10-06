#pragma once

#include "animation/hue_rainbow.h"  // for HueRainbow
#include "display/display.h"        // for Display
#include "games/game.h"             // for Game

namespace kss {
namespace games {
namespace rainbow {

class RainbowGame : public Game {
  animation::HueRainbow background;

 public:
  RainbowGame(display::Display* gameDisplay)
      : Game(gameDisplay), background(2, gameDisplay->size.height) {}

  void setup() override {}

  void loop() override {
    background.Move();
    background.Draw(display);
  }
};

}  // namespace rainbow
}  // namespace games
}  // namespace kss
