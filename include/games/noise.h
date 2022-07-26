/*
Game class
Where the magic happens
*/

#pragma once

#include "animation/noise.h"  // for NoiseAnimation
#include "display/display.h"  // for kss::display::Display
#include "games/game.h"       // for Game

class NoiseGame : public kss::games::Game {
  kss::animation::NoiseAnimation background;

 public:
  NoiseGame(kss::display::Display* gameDisplay)
      : Game{gameDisplay},
        background{gameDisplay->numStrips, gameDisplay->lengthStrips} {}

  void setup() {}

  void loop() { background.draw(display); }
};
