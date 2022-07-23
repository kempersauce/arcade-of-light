#pragma once

#include <Constants.h>
#include <Game.h>

#include "animation/flicker.h"                  // for Flicker
#include "animation/single_color_background.h"  // for SingleColorBG
#include "animation/single_color_block.h"       // for SingleColorBlock

// Test for Directional Pad
class AnimationTest : Game {
 public:
  Flicker* flicker;
  SingleColorBG* bg;
  SingleColorBlock* block;
  int BoundaryBase = 80;
  int BoundaryHeight = 10;

  AnimationTest(Display* gameDisplay) : Game(gameDisplay) {}

  void setup() {
    flicker =
        new Flicker(BoundaryBase, BoundaryHeight, display->numStrips, 0, 55);
    bg = new SingleColorBG(100, 0, 100);
    block = new SingleColorBlock(0, 80, 0, 255, 255);
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
