#pragma once

#include <deque>  // for deque

#include "animation/single_color_background.h"  // for SingleColorBG
#include "controls/dir_pad.h"                   // for kss::controls::DirPad
#include "engines/physics_info.h"               // for PhysicsInfo
#include "games/game.h"                         // for Game

class LaneRunnerGame : Game {
  kss::controls::DirPad controller;
  PhysicsInfo player;
  kss::animation::SingleColorBG background;

  std::deque<int> dots;

 public:
  LaneRunnerGame(kss::display::Display* gameDisplay, kss::controls::DirPad controller)
      : Game(gameDisplay),
        controller{std::move(controller)},
        background(0, 0, 0),
        dots() {}

  virtual void setup() {
    player.xLocation = display->numStrips / 2;
    player.Location = display->lengthStrips * 2 / 3;

    // seed walls with initial stuff
    dots.clear();
    while (dots.size() < display->lengthStrips - 1) {
      dots.push_front(-1);
    }
  }

  void addDots() {
    bool anyDots = false;
    for (int i = 0; i < 10; i++) {
      if (dots[i] >= 0) {
        anyDots = true;
        break;
      }
    }

    dots.pop_back();
    if (anyDots) {
      dots.push_front(-1);
    } else {
      int lane = random16() / (UINT16_MAX / 3);
      switch (lane) {
        case 0:
          // nothing we'll keep this at 0
          lane = 0;
          break;

        case 1:
          lane = display->numStrips / 2;
          break;

        case 2:
          lane = display->numStrips - 1;
          break;

        default:
          lane = 1;
          break;
      }

      dots.push_front(lane);
    }
  }

  virtual void loop() {
    if (controller.up->IsPressed()) {
      player.Velocity = 20;
    } else if (controller.down->IsPressed()) {
      player.Velocity = -20;
    } else {
      player.Velocity = 0;
    }

    if (controller.left->IsPressed()) {
      player.xLocation = 0;
    } else if (controller.right->IsPressed()) {
      player.xLocation = display->numStrips - 1;
    } else {
      player.xLocation = display->numStrips / 2;
    }

    player.Move();
    if (player.Location < 0)
      player.Location = 0;
    else if (player.Location >= display->lengthStrips)
      player.Location = display->lengthStrips - 1;

    addDots();

    if ((int)player.xLocation == dots[(int)player.Location]) {
      dots[(int)player.Location] = -1;
    }

    background.draw(display);

    // draw the dots
    for (int y = 0; y < display->lengthStrips; y++) {
      int lane = dots[y];
      if (lane >= 0) {
        display->strips[lane][y] = CRGB::Magenta;
      }
    }

    // draw player
    display->strips[(int)player.xLocation][(int)player.Location] = CRGB::Green;
  }
};
