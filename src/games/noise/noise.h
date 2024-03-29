#pragma once

#include "animation/noise.h"  // for NoiseAnimation
#include "display/display.h"  // for Display
#include "games/game.h"       // for Game

namespace kss {
namespace games {
namespace noise {

class NoiseGame : public Game {
  animation::NoiseAnimation background;

 public:
  NoiseGame(display::Display* gameDisplay)
      : Game{gameDisplay}, background{gameDisplay->size} {}

  void setup() override {}

  void loop() override { background.Draw(display); }
};

}  // namespace noise
}  // namespace games
}  // namespace kss
