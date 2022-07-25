#include "animation/single_color_background.h"  // for SingleColorBG
#include "games/game.h"                         // for Game

class SingleColorTest : Game {
  SingleColorBG* background;

 public:
  SingleColorTest(Display* gameDisplay) : Game(gameDisplay) {
    background = new SingleColorBG(0, 0, 255);
  }

  void setup() {}

  void loop() { background->draw(display); }
};
