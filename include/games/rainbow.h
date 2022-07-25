/*
Game class
Where the magic happens
*/

#pragma once

#include "animation/hue_rainbow.h"  // for HueRainbow
#include "display/display.h"  // for kss::display::Display
#include "games/game.h"       // for Game
//#include "audio/audio_sender.h"  // for AudioSender

class RainbowGame : Game {
  kss::animation::HueRainbow background;
  // kss::audio::AudioSender* audio;

 public:
  RainbowGame(kss::display::Display* gameDisplay) : Game(gameDisplay), background(2) {
    background.setWaveShift(true);
  }

  void setup() {
    // audio = new kss::audio::AudioSender();
    // audio->playIdleBG();
  }

  void loop() { background.draw(display); }
};
