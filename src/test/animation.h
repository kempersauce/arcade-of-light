#pragma once

#include <vector>  // for vector

#include "animation/animation.h"                // for Animation
#include "animation/single_color_background.h"  // for SingleColorBackground
#include "games/game.h"                         // for Game
#include "serial/debug.h"                       // for Debug

namespace kss {
namespace test {

// Test Game for Animation(s)
class AnimationTest : public games::Game {
  animation::SingleColorBG background;
  std::vector<animation::Animation*> animes;

 public:
  AnimationTest(display::Display* gameDisplay,
                std::vector<animation::Animation*> animus,
                CRGB bg_color = CRGB::Black)
      : Game(gameDisplay), background{bg_color}, animes{animus} {
    animes.insert(animes.begin(), &background);
  }

  AnimationTest(display::Display* gameDisplay, animation::Animation* animus,
                CRGB bg_color = CRGB::Black)
      : Game(gameDisplay), background{bg_color} {
    animes.push_back(&background);
    animes.push_back(animus);
  }

  void setup() override { Debug("Game setup complete"); }

  void loop() override {
    // Move all
    for (auto anime : animes) {
      anime->Move();
    }

    // Draw all
    for (auto anime : animes) {
      anime->Draw(display);
    }
  }
};

}  // namespace test
}  // namespace kss
