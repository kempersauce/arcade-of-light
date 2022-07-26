#pragma once

#include "animation/single_color_background.h"  // for SingleColorBG
#include "display/display.h"  // for kss::display::Display
#include "games/game.h"                         // for Game

class SingleColorTest : public kss::games::Game {
  kss::animation::SingleColorBG background;

 public:
  SingleColorTest(kss::display::Display* gameDisplay) : Game(gameDisplay), background(0, 0, 255)
  {
  }

  void setup() {}

  void loop() { background.draw(display); }
};
