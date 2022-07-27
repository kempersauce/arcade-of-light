#pragma once

#include "animation/hue_rainbow.h"  // for HueRainbow
#include "display/display.h"  // for display::Display
#include "games/game.h"       // for Game
//#include "audio/audio_sender.h"  // for AudioSender

namespace kss {
namespace games {
namespace rainbow {

class RainbowGame : public Game {
  animation::HueRainbow background;
  // audio::AudioSender* audio;

 public:
  RainbowGame(display::Display* gameDisplay) : Game(gameDisplay), background(2) {
    background.setWaveShift(true);
  }

  void setup() {
    // audio = new audio::AudioSender();
    // audio->playIdleBG();
  }

  void loop() { background.draw(display); }
};

}  // namespace rainbow
}  // namespace games
}  // namespace kss
