#pragma once

#include "animation/electric_arc.h"      // for ElectricArc
#include "controls/h2h.h"                // for H2HController
#include "engines/noise.h"               // for NoiseGenerator
#include "games/game.h"                  // for Game
#include "games/head2head/audio.h"       // for H2HAudio
#include "games/head2head/dot.h"         // for H2HDot
#include "games/head2head/game_strip.h"  // for H2HGameStrip
#include "games/head2head/zone.h"        // for H2HZone
#include "games/rainbow/rainbow.h"       // for RainbowGame
#include "time/now.h"                    // for Now

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
  display::Display* const instructo_a;
  display::Display* const instructo_b;
  animation::HueRainbow* const instructo_animation_a;
  animation::HueRainbow* const instructo_animation_b;

  H2HGameState gameState;

  // Idle Game, plays after no buttons have been pressed before idle timeout
  rainbow::RainbowGame idleGame;
  bool isIdle;
  const static uint32_t idleTimeoutMillis = 1000 * 45;  // 45 seconds

  uint32_t totalWinStart = 0;  // timer for win state
  const static uint32_t totalWinTimeoutMillis =
      1000 * 10;  // 10 seconds in win state

  // Each team gets their own audio (well, they will)
  H2HAudio audioA{0};
  H2HAudio audioB{2};

  controls::H2HController teamA;
  controls::H2HController teamB;

  engines::NoiseGenerator noise_generator;

  animation::ElectricArc electricArc;

 public:
  H2HGameStrip** gameStrips;  // one for each strip

  Head2Head(display::Display* gameDisplay, display::Display* instructo_a,
            display::Display* instructo_b, controls::H2HController teamA,
            controls::H2HController teamB)
      : Game(gameDisplay),
        instructo_a{instructo_a},
        instructo_b{instructo_b},
        instructo_animation_a{
            instructo_a == NULL
                ? NULL
                : new animation::HueRainbow(2, instructo_a->size.y)},
        instructo_animation_b{
            instructo_b == NULL
                ? NULL
                : new animation::HueRainbow(2, instructo_b->size.y)},
        idleGame(gameDisplay),
        teamA{std::move(teamA)},
        teamB{std::move(teamB)},
        noise_generator{gameDisplay->size, 30},
        electricArc() {
    // Initialize each game strip
    gameStrips = new H2HGameStrip*[gameDisplay->size.x];

    // Do this one at a time so we can feed it pin numbers and button colors
    for (size_t i = 0; i < gameDisplay->size.x; ++i) {
      gameStrips[i] = new H2HGameStrip(i, gameDisplay->size.y, teamA.buttons[i],
                                       teamB.buttons[i], &noise_generator);
    }
  }

  void setup() {
    enterStartState();
    // enterWinBState();
  }

  void enterStartState() {
    gameState = H2HGameStart;
    audioA.playStdBG();
    audioB.playStdBG();
    audioA.stopWinMusic();
    audioB.stopWinMusic();
    // dont forget to take this out lol
    audioA.ItsTimeToDuel();
    audioB.ItsTimeToDuel();
    for (size_t i = 0; i < display->size.x; i++) {
      gameStrips[i]->reset();
    }
  }

  void enterPlayingState() { gameState = H2HGamePlaying; }

  void enterWinAState() {
    audioA.playTeamAWinGame();
    audioB.playTeamAWinGame();
    gameState = H2HGameWinA;
    for (size_t i = 0; i < display->size.x; i++) {
      gameStrips[i]->enterTotalWinAState();
    }
    totalWinStart = time::Now();
  }

  void enterWinBState() {
    audioA.playTeamBWinGame();
    audioB.playTeamBWinGame();
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
    bool isIdle = true;
    for (size_t i = 0; i < display->size.x; i++) {
      // TODO Move this to the H2HController class IsIdle(..)
      // if any buttons aren't past the idle timeout yet, then we're not idling

      // Check teamA for Idle
      if (i != 0 && i != 4) {  // HACK skip button[5] on team A (it jiggles)
        if (teamA.buttons[i]->GetMillisReleased() <= idleTimeoutMillis) {
          isIdle = false;
          break;
        }
      }

      // Check teamB for idle
      if (i != 3 && i != 7) {  // HACK skip button[5] on team B (it jiggles)
        if (teamB.buttons[i]->GetMillisReleased() <= idleTimeoutMillis) {
          isIdle = false;
          break;
        }
      }
    }

    if (isIdle) {
      Debug("Game is idle!");
      Debug_var(gameState);
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
    // Debug_var(gameState);
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

        for (size_t i = 0; i < display->size.x; i++) {
          gameStrips[i]->checkGameState(audioA, audioB);
        }

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
          gameStrips[i]->Draw(display);
        }
        electricArc.yLocation = H2HGameStrip::midBar;
        electricArc.Draw(display);
        break;
    }

    // Draw instructos

    if (instructo_a != NULL) {
      instructo_animation_a->Move();
      instructo_animation_a->Draw(instructo_a);
    }

    if (instructo_b != NULL) {
      instructo_animation_b->Move();
      instructo_animation_b->Draw(instructo_b);
    }
  }
};

}  // namespace h2h
}  // namespace games
}  // namespace kss
