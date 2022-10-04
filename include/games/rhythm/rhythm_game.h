#pragma once

#include "controls/rhythm.h"             // for RhythmController
#include "display/octo/four_panel.h"     // for FourPanelDisplay
#include "display/sub_display.h"         // for SubDisplay
#include "games/game.h"                  // for Game
#include "games/rhythm/rhythm_single.h"  // for RhythmGameSingle
#include "math/random.h"                 // for random::*
#include "serial/debug.h"                // for Debug

namespace kss {
namespace games {
namespace rhythm {

namespace _rhythm_game {

constexpr uint8_t kNumPlayers{4};

}  // namespace _rhythm_game

class RhythmGame : public Game {
  // List of game instances playing. Infinite multiplayer!
  RhythmGameSingle* players[_rhythm_game::kNumPlayers];

 public:
  RhythmGame(display::octo::FourPanelDisplay* display,
             std::vector<controls::RhythmController> controllers)
      : Game(display) {
    for (uint8_t i = 0; i < _rhythm_game::kNumPlayers; ++i) {
      players[i] = new RhythmGameSingle(&display->panels[i], controllers[i], i);
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
