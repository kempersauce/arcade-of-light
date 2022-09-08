#pragma once

#include "animation/animation.h"  // for Animation
#include "animation/arrow.h"      // for Arrow
#include "animation/starscape.h"  // for Starscape
#include "controls/dir_pad.h"     // for DirPad
#include "games/game.h"           // for Game
#include "serial/debug.h"         // for debug::*

namespace kss {
namespace games {
namespace rhythm {

class RhythmGameSingle : public Game {
  // Sticks
  // controls::DirPad controller;

  // Sounds

  // Animations
  animation::Starscape background;
  animation::Arrow arrow;

 public:
  RhythmGameSingle(display::Display* display)
      : Game(display), background{display->size} {}

  virtual void setup() override { arrow.location.y = display->size.y + 5; }

  virtual void loop() override {
    arrow.location.y--;
    if (arrow.location.y == 0) {
      arrow.location.y = display->size.y + 5;
    }

    background.draw(display);
    arrow.draw(display);
  }
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
