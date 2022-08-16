#pragma once

#include <Constants.h>

#include "animation/animation.h"  // for Animation
#include "games/game.h"           // for Game

namespace kss {
namespace test {

// Test for Directional Pad
class SingleAnimation : public games::Game {
  animation::Animation* anime;

 public:
  SingleAnimation(display::Display* gameDisplay, animation::Animation* animus)
      : Game(gameDisplay), anime{animus} {}

  virtual void setup() override {}

  virtual void loop() override { anime->draw(display); }
};

}  // namespace test
}  // namespace kss
