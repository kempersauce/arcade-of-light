#pragma once

#include <deque>  // for deque

#include "animation/single_color_background.h"  // for SingleColorBG
#include "controls/dir_pad.h"                   // for controls::DirPad
#include "engines/physics_info.h"               // for PhysicsInfo
#include "games/game.h"                         // for Game
#include "math/random.h"                        // for random::*

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
      : Game(gameDisplay), controller{std::move(controller)} {}

  virtual void setup() {
    player.location.x = display->size.x / 2;
    player.location.y = display->size.y * 2 / 3;

    // seed walls with initial stuff
    dots.clear();
    while (dots.size() < display->size.y - 1) {
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
      int lane = math::random::Int8_incl(2);
      switch (lane) {
        case 0:
          // nothing we'll keep this at 0
          lane = 0;
          break;

        case 1:
          lane = display->size.x / 2;
          break;

        case 2:
          lane = display->size.x - 1;
          break;

        default:  // This should not happen
          lane = 1;
          break;
      }

      dots.push_front(lane);
    }
  }

  void loop(const uint32_t now = millis()) override {
    if (controller.up->IsPressed()) {
      player.velocity.y = 20;
    } else if (controller.down->IsPressed()) {
      player.velocity.y = -20;
    } else {
      player.velocity.y = 0;
    }

    if (controller.left->IsPressed()) {
      player.location.x = 0;
    } else if (controller.right->IsPressed()) {
      player.location.x = display->size.x - 1;
    } else {
      player.location.x = display->size.x / 2;
    }

    player.Move();
    if (player.location.y < 0)
      player.location.y = 0;
    else if (player.location.y >= display->size.y)
      player.location.y = display->size.y - 1;

    addDots();

    if ((int)player.location.x == dots[(int)player.location.y]) {
      dots[(int)player.location.y] = -1;
    }

    background.draw(display);

    // draw the dots
    for (int y = 0; y < display->size.y; y++) {
      int lane = dots[y];
      if (lane >= 0) {
        display->Pixel(lane, y) = CRGB::Magenta;
      }
    }

    // draw player
    display->Pixel((int)player.location.x, (int)player.location.y) =
        CRGB::Green;
  }
};

}  // namespace lane_runner
}  // namespace games
}  // namespace kss
