#pragma once

#include <deque>  // for deque

#include "animation/single_color_background.h"  // for SingleColorBG
#include "controls/dir_pad.h"                   // for controls::DirPad
#include "engines/physics_info.h"               // for PhysicsInfo
#include "engines/random.h"                     // for random::*
#include "games/game.h"                         // for Game

namespace kss {
namespace games {
namespace lane_runner {

class LaneRunnerGame : public Game {
  controls::DirPad controller;
  engines::PhysicsInfo player;
  animation::SingleColorBG background;

  std::deque<int> dots;

 public:
  LaneRunnerGame(display::Display* gameDisplay, controls::DirPad controller)
      : Game(gameDisplay),
        controller{std::move(controller)},
        background(0, 0, 0),
        dots() {}

  virtual void setup() {
    player.xLocation = display->strip_count / 2;
    player.Location = display->strip_length * 2 / 3;

    // seed walls with initial stuff
    dots.clear();
    while (dots.size() < display->strip_length - 1) {
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
      int lane = engines::random::Int8_incl(2);
      switch (lane) {
        case 0:
          // nothing we'll keep this at 0
          lane = 0;
          break;

        case 1:
          lane = display->strip_count / 2;
          break;

        case 2:
          lane = display->strip_count - 1;
          break;

        default:  // This should not happen
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
      player.xLocation = display->strip_count - 1;
    } else {
      player.xLocation = display->strip_count / 2;
    }

    player.Move();
    if (player.Location < 0)
      player.Location = 0;
    else if (player.Location >= display->strip_length)
      player.Location = display->strip_length - 1;

    addDots();

    if ((int)player.xLocation == dots[(int)player.Location]) {
      dots[(int)player.Location] = -1;
    }

    background.draw(display);

    // draw the dots
    for (int y = 0; y < display->strip_length; y++) {
      int lane = dots[y];
      if (lane >= 0) {
        display->Pixel(lane, y) = CRGB::Magenta;
      }
    }

    // draw player
    display->Pixel((int)player.xLocation, (int)player.Location) = CRGB::Green;
  }
};

}  // namespace lane_runner
}  // namespace games
}  // namespace kss
