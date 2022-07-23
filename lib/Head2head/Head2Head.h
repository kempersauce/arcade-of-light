#include <Constants.h>
#include <Game.h>
#include <H2HAudio.h>
#include <H2HControl.h>
#include "display/h2h.h"  // for H2HDisplay
#include <H2HDot.h>
#include <H2HGameStrip.h>
#include <H2HZone.h>
#include <LifeGame.h>
#include "engines/noise.h"  // for NoiseGenerator
#include <RainbowGame.h>

#include "animation/electric_arc.h"             // for ElectricArc
#include "animation/single_color_background.h"  // for SingleColorBG
#include "controls/button.h"                    // for Button

enum H2HGameState {
  H2HGameIdle,
  H2HGameStart,
  H2HGamePlaying,
  H2HGameWinA,
  H2HGameWinB,
};

class Head2Head : Game {
  H2HGameState gameState;

  NoiseGenerator noiseGenerator;

  ElectricArc electricArc;

  // Idle Game, plays after no buttons have been pressed before idle timeout
  RainbowGame idleGame;
  bool isIdle;
  const static long idleTimeoutMillis = 1000 * 45;  // 45 seconds

  long totalWinStart = 0;  // timer for win state
  const static long totalWinTimeoutMillis =
      1000 * 10;  // 10 seconds in win state

  H2HAudio* audio;
  bool isFirstSetup = true;

  H2HControl teamA;
  H2HControl teamB;

 public:
  H2HGameStrip** gameStrips;  // one for each strip

  Head2Head(Display* gameDisplay, H2HControl teamA, H2HControl teamB)
      : Game(gameDisplay),
        teamA{std::move(teamA)},
        teamB{std::move(teamB)},
        idleGame(gameDisplay),
        noiseGenerator(gameDisplay->numStrips, gameDisplay->lengthStrips),
        electricArc() {
    noiseGenerator.speed = 30;

    // Initialize each game strip
    gameStrips = new H2HGameStrip*[gameDisplay->numStrips];

    // Do this one at a time so we can feed it pin numbers and button colors
    gameStrips[0] =
        new H2HGameStrip(0, gameDisplay->lengthStrips, teamA.buttons[0],
                         teamB.buttons[0], &noiseGenerator);
    gameStrips[1] =
        new H2HGameStrip(1, gameDisplay->lengthStrips, teamA.buttons[1],
                         teamB.buttons[1], &noiseGenerator);
    gameStrips[2] =
        new H2HGameStrip(2, gameDisplay->lengthStrips, teamA.buttons[2],
                         teamB.buttons[2], &noiseGenerator);
    gameStrips[3] =
        new H2HGameStrip(3, gameDisplay->lengthStrips, teamA.buttons[3],
                         teamB.buttons[3], &noiseGenerator);
    gameStrips[4] =
        new H2HGameStrip(4, gameDisplay->lengthStrips, teamA.buttons[4],
                         teamB.buttons[4], &noiseGenerator);
    gameStrips[5] =
        new H2HGameStrip(5, gameDisplay->lengthStrips, teamA.buttons[5],
                         teamB.buttons[5], &noiseGenerator);
    gameStrips[6] =
        new H2HGameStrip(6, gameDisplay->lengthStrips, teamA.buttons[6],
                         teamB.buttons[6], &noiseGenerator);
    gameStrips[7] =
        new H2HGameStrip(7, gameDisplay->lengthStrips, teamA.buttons[7],
                         teamB.buttons[7], &noiseGenerator);
  }

  void setup() {
    if (isFirstSetup) {
      audio = new H2HAudio();
      isFirstSetup = false;
    }
    enterStartState();
    // enterWinBState();
  }

  void enterStartState() {
    gameState = H2HGameStart;
    audio->playStdBG();
    audio->stopWinMusic();
    // dont forget to take this out lol
    audio->itsTimeToDuel();
    for (int i = 0; i < display->numStrips; i++) {
      gameStrips[i]->reset();
    }
  }

  void enterPlayingState() { gameState = H2HGamePlaying; }

  void enterWinAState() {
    audio->playTeamAWinGame();
    gameState = H2HGameWinA;
    for (int i = 0; i < display->numStrips; i++) {
      gameStrips[i]->enterTotalWinAState();
    }
    totalWinStart = millis();
  }

  void enterWinBState() {
    audio->playTeamBWinGame();
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
      // TODO Move this to the H2HControl class IsIdle(..)
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
        noiseGenerator.fillnoise8();

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
        noiseGenerator.fillnoise8();
        H2HGameStrip::midBar++;

        if (millis() - totalWinStart > totalWinTimeoutMillis) {
          enterStartState();
        }
        break;

      case H2HGameWinB:
        // Generate noise
        noiseGenerator.fillnoise8();
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
