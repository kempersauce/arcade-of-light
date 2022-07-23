/*
Game class
Where the magic happens
*/

#pragma once

#include "display/display.h"  // for Display
#include "games/game.h"  // for Game

#include "animation/noise.h"  // for NoiseAnimation

class NoiseGame : Game {
  NoiseAnimation background;

 public:
  NoiseGame(Display* gameDisplay)
      : Game{gameDisplay},
        background{gameDisplay->numStrips, gameDisplay->lengthStrips} {}

  void setup() {}

  void loop() { background.draw(display); }
};
