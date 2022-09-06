#pragma once

#include "controls/dir_pad.h"    // for DirPad
#include "games/game.h"          // for Game

namespace kss {
namespace games {
namespace rhythm {

class RhythmGameSingle : public Game {
  // Sticks
  controls::DirPad controller;

  // Sounds

  // Animations


 public:
  RhythmGameSingle(display::Display& display,
                   const controls::DirPad& controller)
      : Game(display), controller{controller} {}

  virtual void setup() override {}

  virtual void loop() override {}
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
