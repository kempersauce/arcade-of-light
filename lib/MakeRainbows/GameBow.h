#include <Constants.h>
#include "games/game.h"  // for Game
#include <Rainbow.h>

#define delayVal 90
#define BRIGHTNESS 30

// Rainbow Class
class GameBow : Game {
 public:
  GameBow(Display* gameDisplay) : Game(gameDisplay) {}

  void setup() {
    background = (Animation*)new RainbowAni();
    FastLED.setBrightness(BRIGHTNESS);
  }

  void loop() {
    background->draw(display);
    FastLED.delay(delayVal);
    FastLED.show();
  }
};
