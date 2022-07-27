#pragma once

#include <Constants.h>

#include "animation/dot.h"                      // for Dot
#include "animation/single_color_background.h"  // for SingleColorBG
#include "display/display.h"                    // for Display
#include "games/game.h"                         // for Game

namespace kss {
namespace test {

// Test for Directional Pad
class FiveStripTest : public games::Game {
 public:
  animation::Dot* player;
  animation::SingleColorBG* backgroundColor;

  FiveStripTest(display::Display* gameDisplay) : Game(gameDisplay) {}

  void setStrips() {
    // debug which strip is which
    for (int i = 0; i < display->lengthStrips; i++) {
      display->strips[0][i] = CRGB::Red;
      display->strips[1][i] = CRGB::Green;
      display->strips[2][i] = CRGB::Blue;
      display->strips[3][i] = CRGB::Yellow;
      display->strips[4][i] = CRGB::Violet;
    }
  }

  void setup() { setStrips(); }

  void loop() { setStrips(); }
};

}  // namespace test
}  // namespace kss
