#pragma once

#include "animation/hue_rainbow.h"  // for HueRainbow
#include "animation/marquee.h"      // for Marquee
#include "display/display.h"        // for Display
#include "games/game.h"             // for Game

namespace kss {
namespace games {
namespace marquee {

class MarqueeGame : public Game {
  animation::HueRainbow background;

 public:
  animation::Marquee marquee;

  MarqueeGame(display::Display* gameDisplay)
      : Game(gameDisplay), background(2), marquee(1) {}

  void setup() {
    background.setBrightness(150);
    background.setSaturation(255);
  }

  void loop() {
    background.draw(display);
    marquee.draw(display);
  }
};

}  // namespace marquee
}  // namespace games
}  // namespace kss
