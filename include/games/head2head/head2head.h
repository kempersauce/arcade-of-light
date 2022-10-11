#pragma once

#include "animation/electric_arc.h"              // for ElectricArc
#include "controls/h2h.h"                        // for H2HController
#include "engines/noise.h"                       // for NoiseGenerator
#include "games/game.h"                          // for Game
#include "games/head2head/audio.h"               // for H2HAudio
#include "games/head2head/dot.h"                 // for H2HDot
#include "games/head2head/game_strip.h"          // for H2HGameStrip
#include "games/head2head/h2h_instructo_game.h"  // for H2HInstructoGame
#include "games/head2head/zone.h"                // for H2HZone
#include "games/rainbow/rainbow.h"               // for RainbowGame
#include "time/now.h"                            // for Now

namespace kss {
namespace games {
namespace h2h {

uint8_t zoneAHue = 138;         // teal
uint8_t zoneBHue = 5;           // red
CRGB arc_color = CRGB::Purple;  // Purple

enum H2HGameState {
  H2HGameIdle,
  H2HGameStart,
  H2HGamePlaying,
  H2HGameWinA,
  H2HGameWinB,
};

class Head2Head : public Game {
  H2HInstructoGame* const instructo_a;
  H2HInstructoGame* const instructo_b;

  H2HGameState gameState;

  // Idle Game, plays after no buttons have been pressed before idle timeout
  rainbow::RainbowGame idleGame;
  bool isIdle;

  uint32_t totalWinStart = 0;  // timer for win state
  const static uint32_t totalWinTimeoutMillis =
      1000 * 10;  // 10 seconds in win state

  // Each team gets their own audio
  H2HAudio audioA{0};
  H2HAudio audioB{2};

  controls::H2HController teamA;
  controls::H2HController teamB;

  engines::NoiseGenerator noise_generator;

  animation::ElectricArc electricArc;

 public:
  std::vector<H2HGameStrip*> gameStrips;  // one for each strip

  Head2Head(display::Display* gameDisplay, display::Display* instructo_a,
            display::Display* instructo_b, controls::H2HController teamA,
            controls::H2HController teamB)
      : Game(gameDisplay),
        instructo_a{instructo_a == NULL
                        ? NULL
                        : new H2HInstructoGame(instructo_a, zoneAHue)},
        instructo_b{instructo_b == NULL
                        ? NULL
                        : new H2HInstructoGame(instructo_b, zoneBHue)},
        idleGame(gameDisplay),
        teamA{std::move(teamA)},
        teamB{std::move(teamB)},
        noise_generator{gameDisplay->size, 30},
        electricArc{display->size.width, arc_color} {
    // Initialize each game strip
    // Do this one at a time so we can feed it pin numbers and button colors
    for (size_t i = 0; i < gameDisplay->size.width; ++i) {
      gameStrips.push_back(new H2HGameStrip(
          i, gameDisplay->size.height, teamA.buttons[i], teamB.buttons[i],
          zoneAHue, zoneBHue, arc_color, this->instructo_a, this->instructo_b));
    }
  }

  void setup() {
    if (instructo_a != NULL) {
      instructo_a->setup();
    }

    if (instructo_b != NULL) {
      instructo_b->setup();
    }

    enterStartState();
    // enterWinBState();
  }

  void enterStartState() {
    gameState = H2HGameStart;
    audioB.winBG.Stop();
    audioA.playStdBG();
    // audioB.playStdBG();
    audioA.stopWinMusic();
    audioB.stopWinMusic();
    // dont forget to take this out lol
    audioA.ItsTimeToDuel();
    audioB.ItsTimeToDuel();
    for (auto game_strip : gameStrips) {
      game_strip->reset();
    }

    // bring instructos out of idle
    if (instructo_a != NULL) {
      instructo_a->is_idle = false;
    }
    if (instructo_b != NULL) {
      instructo_b->is_idle = false;
    }
  }

  void enterPlayingState() { gameState = H2HGamePlaying; }

  void enterWinAState() {
    audioA.stdBG.Stop();
    audioA.playTeamAWinGame();
    // audioB.playTeamAWinGame();
    gameState = H2HGameWinA;
    for (auto game_strip : gameStrips) {
      game_strip->enterTotalWinAState();
    }
    totalWinStart = time::Now();
  }

  void enterWinBState() {
    // audioA.playTeamBWinGame();
    audioA.stdBG.Stop();
    audioB.playTeamBWinGame();
    gameState = H2HGameWinB;
    for (auto game_strip : gameStrips) {
      game_strip->enterTotalWinBState();
    }
    totalWinStart = time::Now();
  }

  void enterIdleState() {
    Debug("Entering Idle State");
    gameState = H2HGameIdle;
    idleGame.setup();
    if (instructo_a != NULL) {
      instructo_a->is_idle = true;
      instructo_a->explosions.clear();
    }
    if (instructo_b != NULL) {
      instructo_b->is_idle = true;
      instructo_b->explosions.clear();
    }
  }

  void DrawBackground() {
    noise_generator.fillnoise8();
    for (size_t x = 0; x < display->size.width; ++x) {
      for (size_t y = 0; y < display->size.height; ++y) {
        uint8_t hue;
        if (gameState == H2HGameWinA) {
          hue = zoneAHue;
        } else if (gameState == H2HGameWinB) {
          hue = zoneBHue;
        } else if (y < electricArc.arc[x]) {
          hue = zoneAHue;
        } else {
          hue = zoneBHue;
        }

        display->Pixel(x, y) = CHSV(hue, 255, noise_generator.Data(x, y));
      }
    }
  }

  void loop() override {
    const bool isIdle = teamA.IsIdle() && teamB.IsIdle();

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
        for (auto game_strip : gameStrips) {
          game_strip->checkGameState(audioA, audioB);
        }

        for (auto game_strip : gameStrips) {
          if (game_strip->stripState == H2HStripTotalWinA) {
            enterWinAState();
            break;
          } else if (game_strip->stripState == H2HStripTotalWinB) {
            enterWinBState();
            break;
          }
        }
        break;

      case H2HGameWinA:
        H2HGameStrip::midBar++;

        if (time::Now() - totalWinStart > totalWinTimeoutMillis) {
          enterStartState();
        }
        break;

      case H2HGameWinB:
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
        electricArc.yLocation = H2HGameStrip::midBar;
        electricArc.Move();
        DrawBackground();
        for (auto game_strip : gameStrips) {
          game_strip->Draw(display);
        }
        electricArc.Draw(display);
        break;
    }

    // Run instructos

    if (instructo_a != NULL) {
      instructo_a->loop();
    }

    if (instructo_b != NULL) {
      instructo_b->loop();
    }

    const uint32_t boom_time{5 * 1000};
    bool boom_boom = false;
    if (teamA.buttons[0]->GetMillisHeld() > boom_time &&
        teamA.buttons[1]->GetMillisHeld() > boom_time &&
        teamA.buttons[2]->GetMillisHeld() > boom_time &&
        teamA.buttons[3]->GetMillisReleased() > boom_time &&
        teamA.buttons[4]->GetMillisReleased() > boom_time &&
        teamA.buttons[5]->GetMillisReleased() > boom_time &&
        teamA.buttons[6]->IsDepressing() &&
        teamA.buttons[7]->GetMillisReleased() > boom_time) {
      boom_boom = !boom_boom;
      if (boom_boom) {
        audioA.playIdleBG();
      } else {
        audioA.playStdBG();
      }
    }
  }
};

}  // namespace h2h
}  // namespace games
}  // namespace kss
