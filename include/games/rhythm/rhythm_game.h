#pragma once

#include <vector>  // for std::vector

#include "display/display.h"             // for Display
#include "games/game.h"                  // for Game
#include "games/rhythm/rhythm_single.h"  // for RhythmGameSingle

namespace kss {
namespace games {
namespace rhythm {

class RhythmGame : public Game {
  // List of game instances playing. Infinite multiplayer!
  std::vector<RhythmGameSingle*> players;

 public:
  RhythmGame(display::Display& display,
             const std::vector<RhythmGameSingle*>& players)
      : Game(display), players{players} {}

  virtual void setup() override {}

  virtual void loop() override {}
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
