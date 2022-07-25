/*
Game class
Where the magic happens
*/

#pragma once

#include "animation/hue_rainbow.h"
#include "display/display.h"  // for Display
#include "games/game.h"       // for Game
//#include "audio/audio_sender.h"  // for AudioSender

class RainbowGame : Game {
  HueRainbow background;
  // AudioSender* audio;

 public:
  RainbowGame(Display* gameDisplay) : Game(gameDisplay), background(2) {
    background.setWaveShift(true);
  }

  void setup() {
    // audio = new AudioSender();
    // audio->playIdleBG();
  }

  void loop() { background.draw(display); }
};
