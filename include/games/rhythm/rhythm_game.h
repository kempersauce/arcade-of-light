#pragma once

#include <vector>  // for std::vector

#include "controls/dir_pad.h"            // for DirPad
#include "display/four_panel.h"          // for FourPanelDisplay
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
using namespace _rhythm_game;

class RhythmGame : public Game {
  // List of game instances playing. Infinite multiplayer!
  RhythmGameSingle* players[kNumPlayers];

  std::vector<RhythmGameSingle::ExternalExplosion> external_explosion_hues;

 public:
  RhythmGame(display::FourPanelDisplay* display,
             std::vector<controls::DirPad> controllers)
      : Game(display) {
    for (uint8_t i = 0; i < kNumPlayers; ++i) {
      players[i] = new RhythmGameSingle(&display->panels[i], controllers[i], i,
                                        &external_explosion_hues);
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

    // Test
    // if (math::random::Bool(.01)) {
    //   Debug("Adding explosion");
    //   external_explosion_hues.push_back({math::random::Int8(),
    //                                      math::random::Int8_incl(1, 3),
    //                                      math::random::Int8_incl(1, 3)});
    // }

    if (!external_explosion_hues.empty()) {
      for (auto player : players) {
        player->AddExternalExplosions();
      }

	  Debug("Clearing explosives");
      external_explosion_hues.clear();
	  Debug("Clearing explosives... DONE");
    }
  }
};

}  // namespace rhythm
}  // namespace games
}  // namespace kss
