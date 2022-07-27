#pragma once

#include <Constants.h>

#include "animation/electric_arc.h"             // for ElectricArc
#include "animation/single_color_background.h"  // for SingleColorBG
#include "controls/button.h"                    // for Button
#include "display/h2h.h"                        // for H2HDisplay
#include "engines/noise.h"                      // for NoiseGenerator
#include "games/game.h"                         // for Game
#include "games/head2head/audio.h"              // for H2HAudio
#include "controls/h2h_controller.h"            // for H2HController
#include "games/head2head/dot.h"                // for H2HDot
#include "games/head2head/game_strip.h"         // for H2HGameStrip
#include "games/head2head/zone.h"               // for H2HZone
#include "games/life/life.h"                    // for LifeGame
#include "games/rainbow/rainbow.h"                      // for RainbowGame

namespace kss {
namespace games {
namespace h2h {

enum H2HGameState {
  H2HGameIdle,
  H2HGameStart,
  H2HGamePlaying,
  H2HGameWinA,
  H2HGameWinB,
};

class Head2Head : public kss::games::Game {
  H2HGameState gameState;

  engines::NoiseGenerator noise_engine_;

  animation::ElectricArc electricArc;

  // Idle Game, plays after no buttons have been pressed before idle timeout
  rainbow::RainbowGame idleGame;
  bool isIdle;
  const static long idleTimeoutMillis = 1000 * 45;  // 45 seconds

  long totalWinStart = 0;  // timer for win state
  const static long totalWinTimeoutMillis =
      1000 * 10;  // 10 seconds in win state

  H2HAudio audio;

  controls::H2HController teamA;
  controls::H2HController teamB;

 public:
  H2HGameStrip** gameStrips;  // one for each strip

  Head2Head(display::Display* gameDisplay, controls::H2HController teamA, controls::H2HController teamB)
      : Game(gameDisplay),
        teamA{std::move(teamA)},
        teamB{std::move(teamB)},
        idleGame(gameDisplay),
        noise_engine_{gameDisplay->numStrips, gameDisplay->lengthStrips, 30},
        electricArc() {

    // Initialize each game strip
    gameStrips = new H2HGameStrip*[gameDisplay->numStrips];

    // Do this one at a time so we can feed it pin numbers and button colors
    gameStrips[0] =
        new H2HGameStrip(0, gameDisplay->lengthStrips, teamA.buttons[0],
                         teamB.buttons[0], &noise_engine_);
    gameStrips[1] =
        new H2HGameStrip(1, gameDisplay->lengthStrips, teamA.buttons[1],
                         teamB.buttons[1], &noise_engine_);
    gameStrips[2] =
        new H2HGameStrip(2, gameDisplay->lengthStrips, teamA.buttons[2],
                         teamB.buttons[2], &noise_engine_);
    gameStrips[3] =
        new H2HGameStrip(3, gameDisplay->lengthStrips, teamA.buttons[3],
                         teamB.buttons[3], &noise_engine_);
    gameStrips[4] =
        new H2HGameStrip(4, gameDisplay->lengthStrips, teamA.buttons[4],
                         teamB.buttons[4], &noise_engine_);
    gameStrips[5] =
        new H2HGameStrip(5, gameDisplay->lengthStrips, teamA.buttons[5],
                         teamB.buttons[5], &noise_engine_);
    gameStrips[6] =
        new H2HGameStrip(6, gameDisplay->lengthStrips, teamA.buttons[6],
                         teamB.buttons[6], &noise_engine_);
    gameStrips[7] =
        new H2HGameStrip(7, gameDisplay->lengthStrips, teamA.buttons[7],
                         teamB.buttons[7], &noise_engine_);
  }

  void setup() {
    enterStartState();
    // enterWinBState();
  }

  void enterStartState() {
    gameState = H2HGameStart;
    audio.playStdBG();
    audio.stopWinMusic();
    // dont forget to take this out lol
    audio.itsTimeToDuel();
    for (int i = 0; i < display->numStrips; i++) {
      gameStrips[i]->reset();
    }
  }

  void enterPlayingState() { gameState = H2HGamePlaying; }

  void enterWinAState() {
    audio.playTeamAWinGame();
    gameState = H2HGameWinA;
    for (int i = 0; i < display->numStrips; i++) {
      gameStrips[i]->enterTotalWinAState();
    }
    totalWinStart = millis();
  }

  void enterWinBState() {
    audio.playTeamBWinGame();
    gameState = H2HGameWinB;
    for (int i = 0; i < display->numStrips; i++) {
      gameStrips[i]->enterTotalWinBState();
    }
    totalWinStart = millis();
  }

  void enterIdleState() {
    gameState = H2HGameIdle;
    idleGame.setup();
  }

  void loop() {
    bool isIdle = true;
    for (int i = 0; i < display->numStrips; i++) {
      // TODO Move this to the H2HController class IsIdle(..)
      // if any buttons aren't past the idle timeout yet, then we're not idling
      if (teamA.buttons[i]->GetMillisReleased() <= idleTimeoutMillis ||
          teamB.buttons[i]->GetMillisReleased() <= idleTimeoutMillis) {
        isIdle = false;
      }
    }

    // Switch to idling if we're not already doing it
    if (gameState != H2HGameIdle && isIdle) {
      enterIdleState();
    }

    // Start a new game when we come out of idle
    else if (gameState == H2HGameIdle && isIdle == false) {
      enterStartState();
    }

    // Play the game for one round according to game state
    switch (gameState) {
      case H2HGameIdle:
        idleGame.loop();
        break;

      case H2HGameStart:
        // Go straight into playing for now until we have something here
        enterPlayingState();
        // break;  // Uncomment this once we have something for start game

      case H2HGamePlaying:
        // Generate noise
        noise_engine_.fillnoise8();

        for (int i = 0; i < display->numStrips; i++) {
          gameStrips[i]->checkGameState(audio);
        }

        for (int i = 0; i < display->numStrips; i++) {
          if (gameStrips[i]->stripState == H2HStripTotalWinA) {
            enterWinAState();
            break;
          } else if (gameStrips[i]->stripState == H2HStripTotalWinB) {
            enterWinBState();
            break;
          }
        }
        break;

      case H2HGameWinA:
        // Generate noise
        noise_engine_.fillnoise8();
        H2HGameStrip::midBar++;

        if (millis() - totalWinStart > totalWinTimeoutMillis) {
          enterStartState();
        }
        break;

      case H2HGameWinB:
        // Generate noise
        noise_engine_.fillnoise8();
        H2HGameStrip::midBar--;

        if (millis() - totalWinStart > totalWinTimeoutMillis) {
          enterStartState();
        }
        break;
    }

    // Draw the game according to game state
    switch (gameState) {
      case H2HGameIdle:
        // Do nothing here - idleGame already did it
        break;

      case H2HGameStart:
        // ??
        break;

      case H2HGamePlaying:
      case H2HGameWinA:
      case H2HGameWinB:
        for (int i = 0; i < display->numStrips; i++) {
          gameStrips[i]->draw(display);
        }
        electricArc.yLocation = H2HGameStrip::midBar;
        electricArc.draw(display);
        break;
    }
  }
};

}  // namespace h2h
}  // namespace games
}  // naemspace kss
