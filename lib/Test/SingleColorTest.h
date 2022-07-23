#include <Game.h>
#include <SingleColorBG.h>

class SingleColorTest : Game {
  SingleColorBG* background;

 public:
  SingleColorTest(Display* gameDisplay) : Game(gameDisplay) {
    background = new SingleColorBG(0, 0, 255);
  }

  void setup() {}

  void loop() { background->draw(display); }
};
