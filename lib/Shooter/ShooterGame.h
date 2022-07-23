
#pragma once

#include <Shooter.h>
#include <SingleColorBG.h>
#include <dir_pad.h>

class ShooterGame : Game {
  DirPad controls;
  Shooter shooter;
  Firework bullet;
  SingleColorBG background;

 public:
  ShooterGame(Display* gameDisplay, DirPad controls)
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
      bullet.Move();
    }

    background.draw(display);
    shooter.draw(display);
    if (bullet.isPlaying) {
      bullet.draw(display);
    }
  }
};
