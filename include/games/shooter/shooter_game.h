
#pragma once

#include "animation/single_color_background.h"  // for SingleColorBG
#include "controls/dir_pad.h"                   // for DirPad
#include "games/game.h"                         // for Game
#include "games/rocket/firework.h"              // for Firework
#include "games/shooter/shooter.h"              // for Shooter

namespace kss {
namespace games {
namespace shooter {

class ShooterGame : public Game {
  controls::DirPad controls;
  Shooter shooter;
  rocket::Firework bullet;
  animation::SingleColorBG background;

 public:
  ShooterGame(display::Display* gameDisplay, controls::DirPad controls)
      : Game(gameDisplay),
        controls{std::move(controls)},
        shooter(),
        bullet(gameDisplay->lengthStrips, gameDisplay->numStrips),
        background(0, 0, 0) {}

  virtual void setup() {
    shooter.physics.xLocation = display->numStrips / 2;
    shooter.physics.Location = 20;
  }

  virtual void loop() {
    if (controls.up->IsPressed()) {
      shooter.physics.Velocity = 5;
    } else if (controls.down->IsPressed()) {
      shooter.physics.Velocity = -5;
    } else {
      shooter.physics.Velocity = 0;
    }

    if (controls.left->IsPressed()) {
      shooter.physics.xVelocity = -5;
    } else if (controls.right->IsPressed()) {
      shooter.physics.xVelocity = 5;
    } else {
      shooter.physics.xVelocity = 0;
    }

    if (controls.a->IsDepressing()) {
      if (bullet.isPlaying == false) {
        bullet.Reset();
        bullet.physics.xLocation = shooter.physics.xLocation;
        bullet.physics.Location = shooter.physics.Location;
      }
    }

    shooter.physics.Move();
    if (bullet.isPlaying) {
      // TODO uncomment this once we find a generic solution for fireworks
      // bullet.Move();
    }

    background.draw(display);
    shooter.draw(display);
    if (bullet.isPlaying) {
      bullet.draw(display);
    }
  }
};

}  // namespace shooter
}  // namespace games
}  // namespace kss
