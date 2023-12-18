#pragma once

#include "animation/life.h"                     // for Life
#include "animation/single_color_background.h"  // for SingleColorBG
#include "audio/audio_sender.h"                 // for AudioSender
#include "display/display.h"                    // for Display
#include "games/game.h"                         // for Game
#include "serial/hw_serials.h"                  // for kHwSerials

namespace kss {
namespace games {
namespace life {

class BeamOfLife : public Game {
  // Audio senders
  audio::AudioSender audio_senders[2]{{serial::kHwSerials[0]},
                                      {serial::kHwSerials[1]}};

  // Animations
  animation::SingleColorBG background;
  static constexpr size_t grid_count{3};
  animation::Life life_grids[grid_count];

  int loopCount;
  static constexpr int resetThreshold{300};  // frames until reset
  static constexpr float randomize_density{0.2f};

 public:
  BeamOfLife(display::Display* display)
      : Game(display),
        life_grids{{display->size, CRGB::Magenta, 3},
                   {display->size, CRGB::Yellow, 3},
                   {display->size, CRGB::Cyan, 3}} {}

  void RandomizeAll() {
    for (auto& grid : life_grids) {
      grid.Randomize(randomize_density);
    }
  }

  void setup() override {
    // start off randomized
    RandomizeAll();
  }

  void loop() override {
    // Move each game 1 round
    for (auto& layer : life_grids) {
      layer.Move();
    }

    // Draw to display
    background.Draw(display);
    for (auto& layer : life_grids) {
      layer.Draw(display);
    }

    size_t audio_channel = 0;
    for (auto& layer : life_grids) {
      for (size_t side = 0; side < 4; ++side) {
		// Density often comes in between 0.03 and 0.13
		// So we multiply by 7 to get ~21%-91%
        const float gain = 5 * layer.GetSideDensity(side);
		size_t channel = audio_channel % 6;
		audio_senders[audio_channel / 6].SetChannelGain(channel, gain);
		++audio_channel;
      }
    }

    // Print an example density might look like
    Debug_var(life_grids[0].GetSideDensity(0));
  }
};

}  // namespace life
}  // namespace games
}  // namespace kss
