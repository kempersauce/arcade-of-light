#pragma once

// Rocket flying game
// Game input: 1 Button
// Concept: Press the button to apply upward force to a dot
// Hover the dot in target zone and land to win
// Graph of expected outputs can be found here
// https://docs.google.com/spreadsheets/d/1KmZhmGb0J_XdEv5SdoHkTPB8KuGs9kxIDECwj5WWMT0/edit#gid=1271681145
// Version 0.1

#include "animation/explosion.h"                 // for Explosion
#include "animation/fireworks_show.h"            // for FireworksShow
#include "animation/starscape.h"                 // for Starscape
#include "animation/wave_out.h"                  // for WaveOut
#include "controls/rocket.h"                     // for RocketController
#include "display/display.h"                     // for Display
#include "games/game.h"                          // for Game
#include "games/life/life.h"                     // for LifeGame
#include "games/rocket/audio.h"                  // for RocketAudio
#include "games/rocket/explosions_in_the_sky.h"  // for ExplosionsInTheSky
#include "games/rocket/rocket.h"                 // for Rocket
#include "games/rocket/sky_fade.h"               // for SkyFade
#include "games/rocket/target.h"                 // for Target
#include "time/now.h"                            // for Now

namespace kss {
namespace games {
namespace rocket {

// Game states
enum RocketGameState {
  RocketGameStart,
  RocketGamePlaying,
  RocketGameLose,
  RocketGameLevelAdvance,
  RocketGameWin
};

class RocketGame : public Game {
  display::Display* const instructo;
  animation::WaveOut* const instructo_animation;
  static constexpr uint8_t instructo_play_hue{15};
  static constexpr uint8_t instructo_lose_hue{252};

  // Audio
  RocketAudio audio;

  // Button time
  controls::RocketController controller;

  // Backgrounds
  animation::Starscape starBackground;  // just drawing black empty space for
                                        // now. we are alone in the universe
  SkyFade skyFade;

  // Level progress tracking
  int targetsWon = 0;
  static const int targetsPerLevel = 2;

  int level = 0;
  static const int levelMax = 5;

  // level colors for SkyFade
  CRGB skyFadeColors[levelMax] = {
      {0, 0, 255},    // Blue Earth
      {20, 20, 20},   // Grey Mun
      {255, 0, 0},    // Red Mars
      {255, 96, 0},   // Orange Jupiter
      {128, 0, 128},  // Purple Pluto
  };

  // level colors for targets
  CRGB targetColors[levelMax] = {
      {255, 0, 0},    // Red targets on Blue Earth
      {200, 20, 20},  // Pink targets Grey Mun
      {0, 255, 0},    // Green targets on Orange Mars
      {255, 0, 0},    // Red targets on Jupiter, cuz the big spot or whatever
      {255, 255, 0},  // Yellow targets on Purple Pluto
  };

  // Level values for gravity
  int gravityLevels[levelMax] = {
      15,  // Earth has so much gravities - reset to 15 after testing -Jon
      10,  // Mun is smol
      12,  // Mars is not as stronk, only has this many gravities
      60,  // Jupiter is a big boi
      7,   // poor little old Pluto barely has any gravities, be careful with
           // that button
  };

  // Sprites
  Rocket rocket;  // the player
  Target target;  // the target

  // Game Lose animations
  ExplosionsInTheSky explosionsInTheSky;
  animation::Explosion explosion;

  // Game Win animations
  animation::FireworksShow fireworks;

  // Game State tracker
  // This only tracks the current game state and does not detect game state
  // changes Any code that changes this is expected to update the other objects'
  // state as necessary
  RocketGameState gameState;

 public:
  RocketGame(display::Display* display, display::Display* instructo,
             controls::RocketController controller)
      : Game(display),
        instructo{instructo},
        instructo_animation{instructo == NULL
                                ? NULL
                                : new animation::WaveOut1(instructo_play_hue, 0,
                                                          instructo->size)},
        controller{controller},
        starBackground(display->size, 140),
        skyFade(skyFadeColors[0]),
        rocket(display->size, CRGB::White),
        target(CRGB(55, 0, 0)),
        explosionsInTheSky(),
        explosion{110, 1000, 3000, 55, 12, 0, 0, 255, 0, &audio.explosion},
        fireworks{display->size, 0} {
    // Set some physics on the explosion shrapnel so they'll bounce off the
    // ceiling and floor
    for (auto& shrap : explosion.shrapnel) {
      shrap.LocationMax = display->size.y;
      shrap.BounceFactor = -.8;
    }
  }

  void PlayInstructo() {
    if (instructo != NULL) {
      const float thrust_coefficient =
          min(rocket.physics.thrust.y, rocket.ThrustMax) / rocket.ThrustMax;

      // Saturate to full thrust
      const uint8_t sat = thrust_coefficient * 255.0f;
      // Let the saturation fade until thrust cathes up
      if (sat < instructo_animation->sat) {
        instructo_animation->sat -=
            min(time::LoopElapsedMillis() / 3, instructo_animation->sat);
      } else {
        instructo_animation->sat = sat;
      }

      // Fast speed for warning
      if (thrust_coefficient >= 1) {
        instructo_animation->wave.speed = instructo_animation->SPEED_FAST;
      } else {
        instructo_animation->wave.speed = instructo_animation->SPEED_SLOW;
      }
    }
  }

  void SetInstructoStart() {
    if (instructo_animation != NULL) {
      instructo_animation->hue = instructo_play_hue;
      instructo_animation->sat = 0;
      instructo_animation->wave.speed = instructo_animation->SPEED_SLOW;
    }
  }

  void SetInstructoLose() {
    if (instructo_animation != NULL) {
      instructo_animation->hue = instructo_lose_hue;
      instructo_animation->sat = 255;
      instructo_animation->wave.speed = instructo_animation->SPEED_SLOW;
    }
  }

  // Reset Game
  void setup() override {
    level = 0;
    enterLevelStartState();
  }

  // Reset level
  void enterLevelStartState() {
    Debug("Starting level " + level);
    gameState = RocketGameStart;
    skyFade.color = skyFadeColors[level];
    target.color = targetColors[level];
    target.randomize(display->size.y);
    targetsWon = 0;
    rocket.SetGravity(gravityLevels[level]);
    explosion.SetGravity(gravityLevels[level]);
    rocket.Reset();
    SetInstructoStart();
    audio.playLevelIntro(level);
  }

  void enterWinState() {
    Debug("Entering Win state");
    gameState = RocketGameWin;
    fireworks.SetGravity(gravityLevels[min(level, levelMax - 1)]);
  }

  void enterLoseState() {
    Debug("Entering Lose state");
    gameState = RocketGameLose;
    SetInstructoLose();
    audio.boost.Stop();
    audio.super_boost.Stop();
    audio.lose.Play();
    explosion.ExplodeAt(rocket.physics.location.x, rocket.physics.location.y);
    explosionsInTheSky.startAnimation(audio);
  }

  void enterLevelAdvanceState() {
    Debug("Entering Level Advance state");
    audio.boost.Stop();
    audio.super_boost.Stop();
    audio.playLevelWin();
    rocket.super_boost = true;
    gameState = RocketGameLevelAdvance;
  }

  void enterPlayingState() {
    Debug("Entering Playing state");
    gameState = RocketGamePlaying;
  }

  void checkTarget() {
    bool wasInTarget = target.isInTarget;
    target.isInTarget = rocket.physics.location.y >= target.Loc &&
                        rocket.physics.location.y < target.Loc + target.Height;
    if (target.isInTarget) {
      // Check if we're just entering the target
      if (wasInTarget == false) {
        Debug("Rocket entering target!");
        target.Time = time::Now();
        audio.startPlayTargetHover();
      }

      // Check if we've closed out this target
      else if (target.isTargetLocked()) {
        Debug("Target %d Locked!!", targetsWon);
        // Win state
        targetsWon++;
        audio.stopPlayTargetHover();
        audio.playTargetWin();

        // Still more targets - make a new random target
        if (targetsWon < targetsPerLevel) {
          target.randomize(display->size.y);
        }

        // Last target is on the ground
        else if (targetsWon == targetsPerLevel) {
          target.setToGround();
        }

        // We beat the level
        else if (targetsWon > targetsPerLevel) {
          enterLevelAdvanceState();
        }
      }
    } else if (!target.isInTarget) {
      if (wasInTarget == true) {
        Debug("Rocket leaving target...");
        audio.stopPlayTargetHover();
      }
    }
  }

  // Game Loop
  void loop() override {
    // CHECK FOR MANUALLY-INDUCED GAME STATE CHANGES

    // IDLE CHECK: This enters idle after idleTimeoutMillis, and falls out of
    // idle if a buttons been pressed
    if (gameState != RocketGameWin && controller.IsIdle()) {
      enterWinState();  // just play the win animation here
    }

    // Reset this game if we're just coming out of idle
    if (gameState == RocketGameWin && controller.AnyDepressing()) {
      Debug("Cancelling Win State due to button press");
      setup();  // this sets game state to RocketGameStart
    }

    // Reset this game if they hold the reset button longer than a second (if we
    // havent already lost)
    // if (gameState != RocketGameLose &&
    //     controller.reset->GetMillisHeld() > 1000) {
    //   enterLoseState();
    // }

    // CALCULATE NEW GAME STATE

    switch (gameState) {
      case RocketGameStart:
        // TODO fill this in, right now we just jump into playing state
        enterPlayingState();
        // enterWinState(); // for testing fireworks
        // uncomment this once we have something here, for now just fall through
        // break;

      case RocketGamePlaying:
        rocket.super_boost = controller.super_up->IsPressed();
        if (rocket.super_boost) {
          rocket.physics.thrust.y = rocket.ThrustMax * 2;
        } else {
          // direct correlation between millis held and thrust
          // (rocket caps thrust at 100)
          rocket.physics.thrust.y = controller.up->GetMillisHeld() / 2;
        }

        if (controller.up->IsDepressing()) {
          audio.startPlayBoost();
        }
        if (controller.up->IsReleasing()) {
          audio.stopPlayBoost();
        }

        if (controller.super_up->IsDepressing()) {
          audio.super_boost.Play();
        }
        if (controller.super_up->IsReleasing()) {
          audio.super_boost.Stop();
        }

        rocket.Move();
        PlayInstructo();

        if (rocket.physics.HasExploded) {
          enterLoseState();
        } else {
          checkTarget();
        }
        break;

      case RocketGameLevelAdvance:

        // Boost way way up the screen
        if (rocket.physics.location.y < display->size.height * 4) {
          // just keep boosting up
          if (rocket.physics.thrust.y < rocket.ThrustMax) {
            rocket.physics.thrust.y += 2.5;
            if (rocket.physics.thrust.y > rocket.ThrustMax) {
              rocket.physics.thrust.y = rocket.ThrustMax;
            }
          }
          rocket.physics.respect_edges = false;
          rocket.Move();  // let it boost off the screen

          // shift stars and target down according to Rocket thrust up to 10
          // px/frame
          // int backgroundShift = min(rocket.velocity.y / 32, 6);

          // jk since scale is so high, any higher than 1*scale is too fast, and
          // any lover than 1*scale causes tearing between pixels
          int backgroundShift = 1;
          // NOTE: Since y is actually an 8.8 bit int, this may need more than
          // just a small push
          starBackground.noise_generator->y +=
              backgroundShift * starBackground.noise_generator->scale;
        }

        // Rocket reached top of level, time to start a new one
        else {
          level++;
          if (level == levelMax) {
            // audio.playWin
            //  TODO set up whatever state we need for the Win state to start
            enterWinState();
          } else {
            enterLevelStartState();
          }
        }
        break;

      case RocketGameWin:
        fireworks.Move();
        // TODO fill this in right now we just jump straight into the start
        // state of a new game
        // setup();
        break;

      case RocketGameLose:
        if (explosionsInTheSky.isPlaying()) {
          explosion.Move();
        } else {
          setup();  // reset to new game
        }
        break;
    }

    // Move the stars
    starBackground.Move();

    // DRAW EVERYTHING ACCORDING TO GAME STATE

    switch (gameState) {
      case RocketGameStart:
        // TODO how should this look?
        starBackground.Draw(display);
        skyFade.Draw(display);
        // target.Draw(display);
        // explosionsInTheSky.Draw(display);
        // explosion.Draw(display);
        // fireworks.Draw(display);
        rocket.Draw(display);
        break;

      case RocketGamePlaying:
        starBackground.Draw(display);
        skyFade.Draw(display);
        target.Draw(display);
        // explosionsInTheSky.Draw(display);
        // explosion.Draw(display);
        // fireworks.Draw(display);
        rocket.Draw(display);
        break;

      case RocketGameLose:
        starBackground.Draw(display);
        skyFade.Draw(display);
        // target.Draw(display);
        explosionsInTheSky.Draw(display);
        explosion.Draw(display);
        // fireworks.Draw(display);
        // rocket.Draw(display);
        break;

      case RocketGameLevelAdvance:
        // audio.playLevelWin();
        starBackground.Draw(display);
        skyFade.Draw(display);
        // target.Draw(display);
        // explosionsInTheSky.Draw(display);
        // explosion.Draw(display);
        // fireworks.Draw(display);
        rocket.Draw(display);
        break;

      case RocketGameWin:
        starBackground.Draw(display);
        skyFade.Draw(display);
        // target.Draw(display);
        // explosionsInTheSky.Draw(display);
        // explosion.Draw(display);
        fireworks.Draw(display);
        // rocket.Draw(display);
        break;
    }

    // Draw instructo

    if (instructo != NULL) {
      instructo_animation->Move();
      instructo_animation->Draw(instructo);
    }
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
