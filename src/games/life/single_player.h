#pragma once

#include "controls/dir_pad.h"       // for DirPad
#include "games/game.h"             // for Game
#include "games/life/animation.h"   // for LifeAnimation
#include "games/life/audio.h"       // for LifeAudio
#include "games/rainbow/rainbow.h"  // for RainbowGame
#include "time/now.h"               // for now
#include "time/soft_wait.h"         // for SOFT_WAIT

namespace kss {
namespace games {
namespace life {

enum LifeGameState { LifeGameIdle, LifeGamePlaying };

class LifeGameSinglePlayer : public Game {
  rainbow::RainbowGame idleGame;

  // Controls
  controls::DirPad dirPad;

  // Animations
  LifeAnimation lifeGrid;

  // Sound
  LifeAudio audio;

  uint32_t millisPerFrame = 50;

  // Degrees per millisecond
  const static float hueShiftRate =
      60.0f * (256.0f / 360.0f) / 1000.0f;  // 60 deg/sec?
  float startHue;
  const std::vector<int> hueOffsets{
      // Degrees are converted to int with result = degrees * 256 / 360
      0,    // 0 deg
      43,   // 60 deg
      128,  // 180 deg
      213,  // 300 deg
  };

  bool isPaused = false;

  LifeGameState gameState;

 public:
  LifeGameSinglePlayer(display::Display* display, controls::DirPad controls)
      : Game(display),
        idleGame{display},
        dirPad{std::move(controls)},
        lifeGrid{display->size.x + 1, display->size.y} {
    // Start BG music
    audio.playStdBG();
  }

  void setup() override {
    // Start off on blue
    setHue(140);

    // start off randomized
    lifeGrid.randomize();

    enterPlayingState();
  }

  void enterPlayingState() {
    gameState = LifeGamePlaying;
    audio.playStdBG();
  }

  void enterIdleState() {
    gameState = LifeGameIdle;
    idleGame.setup();
  }

  void loop() override {
    bool isIdle = dirPad.IsIdle();

    // Switch to idling if we're not already doing it
    if (gameState != LifeGameIdle && isIdle) {
      enterIdleState();
    }

    // Start a new game when we come out of idle
    else if (gameState == LifeGameIdle && isIdle == false) {
      enterPlayingState();
    }

    if (gameState == LifeGameIdle) {
      idleGame.loop();
      return;
    }

    // Speed adjust controls
    if (dirPad.up->IsPressed()) {
      millisPerFrame += (float)millisPerFrame / 20.0f;
    }

    if (dirPad.down->IsPressed()) {
      millisPerFrame -= (float)millisPerFrame / 20.0f;
    }

    if (millisPerFrame < 20) {
      millisPerFrame = 20;
    } else if (millisPerFrame > 1000) {
      millisPerFrame = 1000;
    }

    // Hue adjust controls
    if (dirPad.left->IsPressed()) {
      setHue(startHue + hueShiftRate * time::LoopElapsedMillis());
      // audio.playColorShift();
    } else if (dirPad.right->IsPressed()) {
      setHue(startHue - hueShiftRate * time::LoopElapsedMillis());
      // audio.playColorShift();
    } else {
      // audio.stopColorShift();
    }

    // pause/play controls
    if (dirPad.a->IsDepressing()) {
      isPaused = !isPaused;
      if (isPaused) {
        // audio.playTimeStop();
      } else {
        // audio.playTimeStart();
      }
    }

    SOFT_WAIT(millisPerFrame) {
      // randomize controls on frame speed
      if (dirPad.b->IsPressed()) {
        // if(!audio.shuffleIsStarted)
        // {
        //    audio.startRandom();
        // }
        lifeGrid.randomize();
      } else if (isPaused == false) {
        // Calculate next round
        lifeGrid.GoOneRound();
      }
      // if(dirPad.b->IsUp() && audio.shuffleIsStarted)
      // {
      //    audio.stopPlayRandom();
      // }
    }

    // Draw to display
    lifeGrid.Draw(display);
  }

  void setHue(float hue) {
    startHue = hue;
    if (startHue >= 256) {
      startHue -= 256;
    } else if (startHue < 0) {
      startHue += 256;
    }

    lifeGrid.ageColors.clear();
    lifeGrid.ageColors.push_back(CRGB::Black);
    for (size_t i = 0; i < hueOffsets.size(); i++) {
      CRGB color;
      color.setHSV(((int)startHue + hueOffsets[i]) % 256, 255, 255);
      lifeGrid.ageColors.push_back(color);
    }
  }
};

}  // namespace life
}  // namespace games
}  // namespace kss
