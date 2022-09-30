#pragma once

#include <vector>  // for vector

#include "animation/animation.h"                // for Animation
#include "animation/single_color_background.h"  // for SingleColorBackground
#include "games/game.h"                         // for Game

namespace kss {
namespace test {

// Test Game for Animation(s)
class AnimationTest : public games::Game {
  animation::SingleColorBG background;
  std::vector<animation::Animation*> animes;

 public:
  AnimationTest(display::Display* gameDisplay,
                std::vector<animation::Animation*> animus)
      : Game(gameDisplay), animes{animus} {}

  AnimationTest(display::Display* gameDisplay, animation::Animation* animus)
      : Game(gameDisplay) {
    animes.push_back(animus);
  }

  void setup() override {}

  void loop() override {
    for (auto anime : animes) {
      anime->Move();
    }

    background.Draw(display);

    for (auto anime : animes) {
      anime->Draw(display);
    }
  }
};

}  // namespace test
}  // namespace kss
