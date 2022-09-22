#pragma once

#include "animation/single_color_background.h"  // for SingleColorBG
#include "display/display.h"                    // for Display
#include "games/game.h"                         // for Game

namespace kss {
namespace test {

class SingleColorTest : public games::Game {
  animation::SingleColorBG background;

 public:
  SingleColorTest(display::Display* gameDisplay)
      : Game(gameDisplay), background(CRGB::Blue) {}

  void setup() override {}

  void loop(const uint32_t now = millis()) override { background.draw(display); }
};

}  // namespace test
}  // namespace kss
