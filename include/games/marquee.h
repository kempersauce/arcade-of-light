/*
Game class
Where the magic happens
*/

#pragma once

#include "animation/hue_rainbow.h"  // for HueRainbow
#include "animation/marquee.h"      // for Marquee
#include "display/display.h"        // for kss::display::Display
#include "games/game.h"             // for Game

class MarqueeGame : Game {
  kss::animation::HueRainbow background;

 public:
  kss::animation::Marquee marquee;

  MarqueeGame(kss::display::Display* gameDisplay) : Game(gameDisplay), background(2), marquee(1) {
  }

  void setup() {
    background.setBrightness(150);
    background.setSaturation(255);
  }

  void loop() {
    background.draw(display);
    marquee.draw(display);
  }
};
