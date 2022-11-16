#pragma once

#include "animation/life.h"                     // for Life
#include "animation/single_color_background.h"  // for SingleColorBG
#include "display/display.h"                    // for Display
#include "games/game.h"                         // for Game

namespace kss {
namespace games {
namespace life {

class BeamOfLife : public Game {
  // Animations
  animation::SingleColorBG background;
  static constexpr size_t grid_count{3};
  animation::Life life_grids[grid_count];

  int loopCount;
  static const int resetThreshold = 300;  // frames until reset
  static constexpr float randomize_density{0.2f};

 public:
  BeamOfLife(display::Display* display)
      : Game(display),
        life_grids{{display->size, CRGB::Red, 3},
                   {display->size, CRGB::Green, 3},
                   {display->size, CRGB::Blue, 3}} {}

  void RandomizeAll() {
    loopCount = 0;
    for (auto& grid : life_grids) {
      grid.Randomize(randomize_density);
    }
  }

  void setup() override {
    // start off randomized
    RandomizeAll();
  }

  void loop() override {
    // Calculate next round
    if (loopCount++ >= resetThreshold) {
      RandomizeAll();
    }

    for (auto& grid : life_grids) {
      grid.GoOneRound();
    }

    // Draw to display
    background.Draw(display);
    for (auto& grid : life_grids) {
      grid.Draw(display);
    }
  }
};

}  // namespace life
}  // namespace games
}  // namespace kss
