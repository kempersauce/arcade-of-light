
#pragma once

#include "animation/firework.h"                 // for Firework
#include "animation/single_color_background.h"  // for SingleColorBG
#include "controls/dir_pad.h"                   // for DirPad
#include "games/game.h"                         // for Game
#include "games/shooter/shooter.h"              // for Shooter

namespace kss {
namespace games {
namespace shooter {

class ShooterGame : public Game {
  controls::DirPad controls;
  Shooter shooter;
  animation::Firework bullet;
  animation::SingleColorBG background;

 public:
  ShooterGame(display::Display* display, controls::DirPad controls)
      : Game(display),
        controls{std::move(controls)},
        shooter(),
        bullet(display->strip_length, display->strip_count, 0, NULL, NULL),
        background(0, 0, 0) {}

  virtual void setup() {
    shooter.physics.location.x = display->strip_count / 2;
    shooter.physics.location.y = 20;
  }

  virtual void loop() {
    if (controls.up->IsPressed()) {
      shooter.physics.velocity.y = 5;
    } else if (controls.down->IsPressed()) {
      shooter.physics.velocity.y = -5;
    } else {
      shooter.physics.velocity.y = 0;
    }

    if (controls.left->IsPressed()) {
      shooter.physics.velocity.x = -5;
    } else if (controls.right->IsPressed()) {
      shooter.physics.velocity.x = 5;
    } else {
      shooter.physics.velocity.x = 0;
    }

    if (controls.a->IsDepressing()) {
      if (bullet.isPlaying == false) {
        bullet.Reset();
        bullet.physics.location.x = shooter.physics.location.x;
        bullet.physics.location.y = shooter.physics.location.y;
      }
    }

    shooter.physics.Move();
	// TODO this will not work with the way we track isPlaying in firework.h
	// Instead we should allocate and destroy fireworks as needed
    if (bullet.isPlaying) {
      bullet.Move();
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
