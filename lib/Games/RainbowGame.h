/*
Game class
Where the magic happens
*/

#pragma once

#include "display/display.h"  // for Display
#include <Game.h>

#include "animation/hue_rainbow.h"
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
