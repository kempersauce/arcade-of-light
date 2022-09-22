#pragma once

#include "animation/electric_arc.h"             // for ElectricArc
#include "animation/single_color_background.h"  // for SingleColorBG
#include "controls/button.h"                    // for Button
#include "controls/h2h_controller.h"            // for H2HController
#include "display/h2h_octo.h"                   // for H2HDisplay
#include "engines/noise.h"                      // for NoiseGenerator
#include "games/game.h"                         // for Game
#include "games/head2head/audio.h"              // for H2HAudio
#include "games/head2head/dot.h"                // for H2HDot
#include "games/head2head/game_strip.h"         // for H2HGameStrip
#include "games/head2head/zone.h"               // for H2HZone
#include "games/life/life.h"                    // for LifeGame
#include "games/rainbow/rainbow.h"              // for RainbowGame
#include "time/now.h"                           // for Now

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

class Head2Head : public Game {
  H2HGameState gameState;

  // Idle Game, plays after no buttons have been pressed before idle timeout
  rainbow::RainbowGame idleGame;
  bool isIdle;
  const static uint32_t idleTimeoutMillis = 1000 * 45;  // 45 seconds

  uint32_t totalWinStart = 0;  // timer for win state
  const static uint32_t totalWinTimeoutMillis =
      1000 * 10;  // 10 seconds in win state

  H2HAudio audio;

  controls::H2HController teamA;
  controls::H2HController teamB;

  engines::NoiseGenerator noise_generator;

  animation::ElectricArc electricArc;

 public:
  H2HGameStrip** gameStrips;  // one for each strip

  Head2Head(display::Display* gameDisplay, controls::H2HController teamA,
            controls::H2HController teamB)
      : Game(gameDisplay),
        idleGame(gameDisplay),
        teamA{std::move(teamA)},
        teamB{std::move(teamB)},
        noise_generator{gameDisplay->size, 30},
        electricArc() {
    // Initialize each game strip
    gameStrips = new H2HGameStrip*[gameDisplay->size.x];

    // Do this one at a time so we can feed it pin numbers and button colors
    gameStrips[0] = new H2HGameStrip(0, gameDisplay->size.y, teamA.buttons[0],
                                     teamB.buttons[0], &noise_generator);
    gameStrips[1] = new H2HGameStrip(1, gameDisplay->size.y, teamA.buttons[1],
                                     teamB.buttons[1], &noise_generator);
    gameStrips[2] = new H2HGameStrip(2, gameDisplay->size.y, teamA.buttons[2],
                                     teamB.buttons[2], &noise_generator);
    gameStrips[3] = new H2HGameStrip(3, gameDisplay->size.y, teamA.buttons[3],
                                     teamB.buttons[3], &noise_generator);
    gameStrips[4] = new H2HGameStrip(4, gameDisplay->size.y, teamA.buttons[4],
                                     teamB.buttons[4], &noise_generator);
    gameStrips[5] = new H2HGameStrip(5, gameDisplay->size.y, teamA.buttons[5],
                                     teamB.buttons[5], &noise_generator);
    gameStrips[6] = new H2HGameStrip(6, gameDisplay->size.y, teamA.buttons[6],
                                     teamB.buttons[6], &noise_generator);
    gameStrips[7] = new H2HGameStrip(7, gameDisplay->size.y, teamA.buttons[7],
                                     teamB.buttons[7], &noise_generator);
  }

  void setup() {
    enterStartState();
    // enterWinBState();
  }

  void enterStartState() {
    Debug("Entering Start State");
    gameState = H2HGameStart;
    audio.playStdBG();
    audio.stopWinMusic();
    // dont forget to take this out lol
    audio.ItsTimeToDuel();
    for (size_t i = 0; i < display->size.x; i++) {
      gameStrips[i]->reset();
    }
  }

  void enterPlayingState() { gameState = H2HGamePlaying; }

  void enterWinAState() {
    audio.playTeamAWinGame();
    gameState = H2HGameWinA;
    for (size_t i = 0; i < display->size.x; i++) {
      gameStrips[i]->enterTotalWinAState();
    }
    totalWinStart = time::Now();
  }

  void enterWinBState() {
    audio.playTeamBWinGame();
    gameState = H2HGameWinB;
    for (size_t i = 0; i < display->size.x; i++) {
      gameStrips[i]->enterTotalWinBState();
    }
    totalWinStart = time::Now();
  }

  void enterIdleState() {
    Debug("Entering Idle State");
    gameState = H2HGameIdle;
    idleGame.setup();
  }

  void loop() override {
    Debug("Loop Begins here");
    bool isIdle = true;
    for (size_t i = 0; i < display->size.x; i++) {
      // TODO Move this to the H2HController class IsIdle(..)
      // if any buttons aren't past the idle timeout yet, then we're not idling
      if (teamA.buttons[i]->GetMillisReleased() <= idleTimeoutMillis ||
          teamB.buttons[i]->GetMillisReleased() <= idleTimeoutMillis) {
        isIdle = false;
        break;
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
    Debug("Entering gameState switch");
    Debug_var(gameState);
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
        noise_generator.fillnoise8();

        Debug("Checking game strip states...");
        for (size_t i = 0; i < display->size.x; i++) {
          gameStrips[i]->checkGameState(audio);
        }

        Debug("Checking strip win states...");
        for (size_t i = 0; i < display->size.x; i++) {
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
        noise_generator.fillnoise8();
        H2HGameStrip::midBar++;

        if (time::Now() - totalWinStart > totalWinTimeoutMillis) {
          enterStartState();
        }
        break;

      case H2HGameWinB:
        // Generate noise
        noise_generator.fillnoise8();
        H2HGameStrip::midBar--;

        if (time::Now() - totalWinStart > totalWinTimeoutMillis) {
          enterStartState();
        }
        break;
    }

    Debug("Drawing Begins here");

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
        for (size_t i = 0; i < display->size.x; i++) {
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
}  // namespace kss
