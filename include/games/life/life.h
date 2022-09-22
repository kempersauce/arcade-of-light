#pragma once

#include "display/display.h"       // for Display
#include "games/game.h"            // for Game
#include "games/life/animation.h"  // for LifeAnimation

namespace kss {
namespace games {
namespace life {

class LifeGame : public Game {
  // Animations
  LifeAnimation lifeGrid;

  int loopCount;
  static const int resetThreshold = 300;  // frames until reset

 public:
  LifeGame(display::Display* display)
      : Game(display), lifeGrid{display->size.x, display->size.y} {}

  void setup() override {
    loopCount = 0;
    // start off randomized
    lifeGrid.randomize();
  }

  void loop(const uint32_t now = millis()) override {
    if (loopCount++ >= resetThreshold) {
      setup();
    }

    // Calculate next round
    lifeGrid.GoOneRound();

    // Draw to display
    lifeGrid.draw(display);
  }
};

}  // namespace life
}  // namespace games
}  // namespace kss
