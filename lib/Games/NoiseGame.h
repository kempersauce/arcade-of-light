/*
Game class
Where the magic happens
*/

#pragma once

#include <Display.h>
#include <Game.h>

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
