#pragma once

#include "animation/explosions.h"   // for Explosions
#include "animation/hue_rainbow.h"  // for HueRainbow
#include "animation/wave_out.h"     // for WaveOut
#include "display/display.h"        // for Display
#include "games/game.h"             // for Game

namespace kss {
namespace games {
namespace h2h {

class H2HInstructoGame : public Game {
 public:
  bool is_idle{false};
  animation::HueRainbow idle;
  animation::WaveOut2 background;

  // Keep explosions to show when the other team scores on us
  animation::Explosions explosions;

  H2HInstructoGame(display::Display* display, uint8_t hue)
      : Game(display),
        idle{0, display->size.height},
        background{hue, 255, display->size} {
    idle.setWaveStats(6, -3, 3);
  }

  void ExplodeBack(uint8_t game_strip) {
    explosions.back().ExplodeAt(
        0, game_strip * display->size.height / 8 + display->size.height / 16);
  }

  void setup() override {}

  void loop() override {
    if (is_idle) {
      idle.Move();
      idle.Draw(display);
    } else {
      background.Move();
      explosions.Move();

      background.Draw(display);
      explosions.Draw(display);
    }
  }
};

}  // namespace h2h
}  // namespace games
}  // namespace kss
