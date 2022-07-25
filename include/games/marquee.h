/*
Game class
Where the magic happens
*/

#pragma once

#include "animation/hue_rainbow.h"  // for HueRainbow
#include "animation/marquee.h"      // for Marquee
#include "display/display.h"        // for Display
#include "games/game.h"             // for Game

class MarqueeGame : Game {
  HueRainbow* background;

 public:
  Marquee* marquee;

  MarqueeGame(Display* gameDisplay) : Game(gameDisplay) {
    background = new HueRainbow(2);
    marquee = new Marquee(1);
  }

  void setup() {
    ((HueRainbow*)background)->setBrightness(150);
    ((HueRainbow*)background)->setSaturation(255);
  }

  void loop() {
    background->draw(display);
    marquee->draw(display);
  }
};
