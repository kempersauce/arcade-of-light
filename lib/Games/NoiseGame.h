/*
Game class
Where the magic happens
*/

#pragma once

#include <Game.h>
#include <Noise.h>

class NoiseGame : Game {
  NoiseAnimation background;

 public:
  NoiseGame(Display* gameDisplay)
      : Game{gameDisplay},
        background{gameDisplay->numStrips, gameDisplay->lengthStrips} {}

  void setup() {}

  void loop() { background.draw(display); }
};
