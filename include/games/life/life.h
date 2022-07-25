#pragma once

#include "display/display.h"       // for Display
#include "games/game.h"            // for Game
#include "games/life/animation.h"  // for LifeAnimation

class LifeGame : Game {
  // Animations
  LifeAnimation* lifeGrid;

  int loopCount;
  static const int resetThreshold = 300;  // frames until reset

 public:
  LifeGame(Display* display) : Game(display) {
    lifeGrid = new LifeAnimation(display->numStrips, display->lengthStrips);
  }

  void setup() {
    loopCount = 0;
    // start off randomized
    lifeGrid->randomize();
  }

  virtual void loop() {
    if (loopCount++ >= resetThreshold) {
      setup();
    }

    // Calculate next round
    lifeGrid->GoOneRound();

    // Draw to display
    lifeGrid->draw(display);
  }
};
