#pragma once

// Rocket flying game
// Game input: 1 Button
// Concept: Press the button to apply upward force to a dot
// Hover the dot in target zone and land to win
// Graph of expected outputs can be found here
// https://docs.google.com/spreadsheets/d/1KmZhmGb0J_XdEv5SdoHkTPB8KuGs9kxIDECwj5WWMT0/edit#gid=1271681145
// Version 0.1

#define LED_PIN \
  1  // OUTPUT pin WS2812B LED Strip is attached to input is GRB not RGB

#define delayval 25        // controls the "speed" of the rocket dot
#define animationDelay 50  // controls the speed of the win animation

#define BRIGHTNESS 50

#include "animation/fireworks_show.h"  // for FireworksShow
#include "animation/starscape.h"       // for Starscape
#include "controls/button.h"           // for Button
#include "display/display.h"           // for Display
#include "games/game.h"                // for Game
#include "games/rocket/rocket.h"       // for Rocket
#include "games/rocket/sky_fade.h"     // for SkyFade
#include "games/rocket/target.h"       // for Target
#include "time/now.h"                  // for Now
//#include "audio/sounds.h"  // for Sounds
#include <vector>

#include "animation/explosion.h"                 // for Explosion
#include "games/life/life.h"                     // for LifeGame
#include "games/rocket/audio.h"                  // for RocketAudio
#include "games/rocket/explosions_in_the_sky.h"  // for ExplosionsInTheSky

namespace kss {
namespace games {
namespace rocket {

bool boostIsPlaying = false;
bool targetIsPlaying = false;

// Game states
enum RocketGameState {
  RocketGameStart,
  RocketGamePlaying,
  RocketGameLose,
  RocketGameLevelAdvance,
  RocketGameWin
};

class RocketGame : public Game {
  // Audio
  RocketAudio audio;

  // Button time
  controls::Button* up_btn;
  controls::Button* reset_btn;

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
  CRGB* skyFadeColors[levelMax] = {
      new CRGB(0, 0, 255),    // Blue Earth
      new CRGB(20, 20, 20),   // Grey Mun
      new CRGB(255, 0, 0),    // Red Mars
      new CRGB(255, 96, 0),   // Orange Jupiter
      new CRGB(128, 0, 128),  // Purple Pluto
  };

  // level colors for targets
  CRGB* targetColors[levelMax] = {
      new CRGB(255, 0, 0),    // Red targets on Blue Earth
      new CRGB(200, 20, 20),  // Pink targets Grey Mun
      new CRGB(0, 255, 0),    // Green targets on Orange Mars
      new CRGB(255, 0,
               0),  // Red targets on Jupiter, cuz the big spot or whatever
      new CRGB(255, 255, 0),  // Yellow targets on Purple Pluto
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

  animation::FireworksShow fireworks;  // win animation fireworks

  // Game Lose animations
  animation::Explosion explosion;
  ExplosionsInTheSky explosionsInTheSky;

  // Game State tracker
  // This only tracks the current game state and does not detect game state
  // changes Any code that changes this is expected to update the other objects'
  // state as necessary
  RocketGameState gameState;

  // Fireworks animation plays after no buttons have been pressed before idle
  // timeout
  const uint32_t idleTimeoutMillis = 1000 * 30;  // 30 seconds

 public:
  RocketGame(display::Display* display, controls::Button* up,
             controls::Button* reset)
      : Game(display),
        up_btn{std::move(up)},
        reset_btn{std::move(reset)},
        starBackground(display->size, 140),
        skyFade(skyFadeColors[0]),
        rocket(display->size.y, new CRGB(255, 255, 255)),
        target(new CRGB(55, 0, 0)),
        explosionsInTheSky(),
        explosion{80, 1000, 3000, 20, 18, 1.8, 0, 255, 0, &audio.explosion},
        fireworks{display->size, 0} {
    // Set some physics on the explosion shrapnel so they'll bounce off the
    // ceiling and floor
    for (auto& shrap : explosion.shrapnel) {
      shrap.LocationMax = display->size.y;
      shrap.BounceFactor = -.8;
    }
  }

  // Reset Game
  void setup() {
    audio.playStdBG();
    level = 0;
    enterLevelStartState();
  }

  // Reset level
  void enterLevelStartState() {
    gameState = RocketGameStart;
    skyFade.setFadeColor(skyFadeColors[level]);
    target.setColor(targetColors[level]);
    target.randomize(display->size.y);
    targetsWon = 0;
    rocket.SetGravity(gravityLevels[level]);
    rocket.Reset();
    audio.playLevelIntro(level);
  }

  void enterWinState() {
    gameState = RocketGameWin;
    fireworks.SetGravity(gravityLevels[min(level, levelMax - 1)]);
    audio.playWinBG();
  }

  void enterLoseState() {
    // game stuff
    gameState = RocketGameLose;
    explosion.ExplodeAt(display->size.x / 2, rocket.physics.location.y);
    explosionsInTheSky.startAnimation(audio);
  }

  void enterLevelAdvanceState() {
    // AUDIO HERE MUST BE SERIAL PRINT OTHERWISE BREAKS GAME STATE!!!
    audio.playLevelWin();
    gameState = RocketGameLevelAdvance;
    // No other changes required for this state change
  }

  void enterPlayingState() {
    gameState = RocketGamePlaying;
    // No other changes required for this state change
  }

  void checkTarget() {
    bool wasInTarget = target.isInTarget;
    target.isInTarget = rocket.physics.location.y >= target.Loc &&
                        rocket.physics.location.y < target.Loc + target.Height;
    if (target.isInTarget) {
      // Check if we're just entering the target
      if (wasInTarget == false) {
        target.Time = time::Now();
        audio.startPlayTargetHover();
      }

      // Check if we've closed out this target
      else if (target.isTargetLocked()) {
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
        audio.stopPlayTargetHover();
      }
    }
  }

  // Game Loop
  void loop() override {
    // CHECK FOR MANUALLY-INDUCED GAME STATE CHANGES

    // IDLE CHECK: This enters idle after idleTimeoutMillis, and falls out of
    // idle if a buttons been pressed
    if (gameState != RocketGameWin &&
        up_btn->GetMillisReleased() > idleTimeoutMillis &&
        reset_btn->GetMillisReleased() > idleTimeoutMillis) {
      enterWinState();  // just play the win animation here
    }

    // Reset this game if we're just coming out of idle
    if (gameState == RocketGameWin &&
        (up_btn->IsDepressing() || reset_btn->IsDepressing())) {
      setup();  // this sets game state to RocketGameStart
    }

    // Reset this game if they hold the reset button longer than a second (if we
    // havent already lost)
    if (gameState != RocketGameLose && reset_btn->GetMillisHeld() > 1000) {
      enterLoseState();
    }

    // CALCULATE NEW GAME STATE

    switch (gameState) {
      case RocketGameStart:
        // TODO fill this in, right now we just jump into playing state
        enterPlayingState();
        // enterWinState(); // for testing fireworks
        // break; // uncomment this once we have something here, right now we
        // just fall through

      case RocketGamePlaying:
        rocket.SetBoost(
            up_btn->GetMillisHeld());  // direct correlation between millis held
                                       // and thrust (rocket caps it at
                                       // ThrustMax=200)
        if (up_btn->IsDepressing()) {
          audio.startPlayBoost();
        }
        if (up_btn->IsReleasing()) {
          audio.stopPlayBoost();
          boostIsPlaying = false;
        }

        rocket.Move();

        if (rocket.physics.HasExploded) {
          enterLoseState();
        } else {
          checkTarget();
        }
        break;

      case RocketGameLevelAdvance:

        // Boost way way up the screen
        if (rocket.physics.location.y < display->size.y * 2) {
          rocket.SetBoost(rocket.physics.thrust.y +
                          5);  // just keep boosting up
          rocket.physics.respect_edges = false;
          rocket.Move();  // let it boost off the screen

          // shift stars and target down according to Rocket thrust up to 10
          // px/frame
          // int backgroundShift = min(rocket.velocity.y / 32, 6);

          // jk since scale is so high, any higher than 1*scale is too fast, and
          // any lover than 1*cale causes tearing between pixels
          int backgroundShift = 1;
          starBackground.noise_generator.y +=
              backgroundShift *
              starBackground.noise_generator
                  .scale;  // NOTE: Since y is actually an 8.8 bit int, this may
                           // need more than just a small push
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

    // DRAW EVERYTHING ACCORDING TO GAME STATE

    switch (gameState) {
      case RocketGameStart:
        // TODO how should this look?
        starBackground.draw(display);
        skyFade.draw(display);
        // target.draw(display);
        // explosionsInTheSky.draw(display);
        // explosion.draw(display);
        // fireworks.draw(display);
        rocket.draw(display);
        break;

      case RocketGamePlaying:
        starBackground.draw(display);
        skyFade.draw(display);
        target.draw(display);
        // explosionsInTheSky.draw(display);
        // explosion.draw(display);
        // fireworks.draw(display);
        rocket.draw(display);
        break;

      case RocketGameLose:
        starBackground.draw(display);
        skyFade.draw(display);
        // target.draw(display);
        explosionsInTheSky.draw(display);
        explosion.draw(display);
        // fireworks.draw(display);
        // rocket.draw(display);
        break;

      case RocketGameLevelAdvance:
        // audio.playLevelWin();
        starBackground.draw(display);
        skyFade.draw(display);
        // target.draw(display);
        // explosionsInTheSky.draw(display);
        // explosion.draw(display);
        // fireworks.draw(display);
        rocket.draw(display);
        break;

      case RocketGameWin:
        starBackground.draw(display);
        skyFade.draw(display);
        // target.draw(display);
        // explosionsInTheSky.draw(display);
        // explosion.draw(display);
        fireworks.draw(display);
        // rocket.draw(display);
        break;
    }
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
