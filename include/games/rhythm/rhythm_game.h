#pragma once

#include <vector>  // for std::vector

#include "display/four_panel.h"          // for FourPanelDisplay
#include "display/sub_display.h"         // for SubDisplay
#include "games/game.h"                  // for Game
#include "games/rhythm/rhythm_single.h"  // for RhythmGameSingle
#include "serial/debug.h"                // for Debug

namespace kss {
namespace games {
namespace rhythm {

namespace _rhythm_game {

constexpr uint8_t kNumPlayers{4};

}  // namespace _rhythm_game
using namespace _rhythm_game;

class RhythmGame : public Game {
  // List of game instances playing. Infinite multiplayer!
  RhythmGameSingle* players[kNumPlayers];

 public:
  RhythmGame(display::FourPanelDisplay* display) : Game(display) {
    for (uint8_t i = 0; i < kNumPlayers; ++i) {
      players[i] = new RhythmGameSingle(&display->panels[i], i);
    }
  }

  void setup() override {
    for (auto player : players) {
      player->setup();
    }
  }

  void loop() override {
    for (auto player : players) {
      player->loop();
    }
  }
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
