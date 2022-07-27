#pragma once

#include <Constants.h>

#include "animation/flicker.h"                  // for Flicker
#include "animation/single_color_background.h"  // for SingleColorBG
#include "animation/single_color_block.h"       // for SingleColorBlock
#include "games/game.h"                         // for Game

namespace kss {
namespace test {

// Test for Directional Pad
class AnimationTest : public games::Game {
 public:
  animation::Flicker* flicker;
  animation::SingleColorBG* bg;
  animation::SingleColorBlock* block;
  int BoundaryBase = 80;
  int BoundaryHeight = 10;

  AnimationTest(display::Display* gameDisplay) : Game(gameDisplay) {}

  void setup() {
    flicker = new animation::Flicker(BoundaryBase, BoundaryHeight,
                                     display->numStrips, 0, 55);
    bg = new animation::SingleColorBG(100, 0, 100);
    block = new animation::SingleColorBlock(0, 80, 0, 255, 255);
  }

  void loop() {
    bg->draw(display);
    block->draw(display);
    flicker->draw(display);
    for (int i = 0; i < display->numStrips; i++) {
      display->strips[i][BoundaryBase].setHSV(125, 255, 255);
      display->strips[i][BoundaryBase + BoundaryHeight].setHSV(125, 255, 255);
    }
  }
};

}  // namespace test
}  // namespace kss
