
#pragma once

#include <deque>    // for deque
#include <utility>  // for pair

#include "animation/single_color_background.h"  // for SingleColorBG
#include "controls/dir_pad.h"                   // for DirPad
#include "engines/physics_info.h"               // for PhysicsInfo
#include "games/game.h"                         // for Game
#include "math/random.h"                        // for random::*

namespace kss {
namespace games {
namespace falling {

class FallingGame : public Game {
  controls::DirPad controls;
  engines::PhysicsInfo player;
  animation::SingleColorBG background;

  std::deque<std::pair<int, int>> walls;

 public:
  FallingGame(display::Display* gameDisplay, controls::DirPad controls)
      : Game(gameDisplay), controls{std::move(controls)} {}

  virtual void setup() {
    player.location.x = display->size.x / 2;
    player.location.y = display->size.y * 2 / 3;

    // seed walls with initial stuff
    walls.clear();
    while (walls.size() < display->size.y - 1) {
      walls.push_front(std::make_pair(-1, display->size.x));
    }
  }

  void addWalls() {
    int left;
    int right;
    do {
      left = walls.front().first + math::random::Int8_incl(-1, 1);
      right = walls.front().second + math::random::Int8_incl(-1, 1);

      // Prevent the random walk from going more than 1 outside the visible
      // range
      if (left < -1) left = -1;

      if (right > display->size.x) right = display->size.x;

      // TODO check if left < right

      // Cap this at 2 pixel width tunnel
    } while (right - left < (display->size.x + 1) / 2);

    walls.pop_back();
    walls.push_front(std::make_pair(left, right));
  }

  void loop() override {
    if (controls.up->IsPressed()) {
      player.velocity.y = 10;
    } else if (controls.down->IsPressed()) {
      player.velocity.y = -10;
    } else {
      player.velocity.y = 0;
    }

    if (controls.left->IsPressed()) {
      player.velocity.x = -10;
    } else if (controls.right->IsPressed()) {
      player.velocity.x = 10;
    } else {
      player.velocity.x = 0;
    }

    player.Move();
    if (player.location.y < 0)
      player.location.y = 0;
    else if (player.location.y >= display->size.y)
      player.location.y = display->size.y - 1;

    if (player.location.x < 0)
      player.location.x = 0;
    else if (player.location.x >= display->size.x)
      player.location.x = display->size.x - 1;

    addWalls();

    if (player.location.x <= walls[(int)player.location.y].first ||
        player.location.x >= walls[(int)player.location.y].second) {
      setup();
    }

    background.Draw(display);

    // Draw the walls
    for (int y = 0; y < display->size.y; y++) {
      for (int x = 0; x <= walls[y].first; x++) {
        display->Pixel(x, y) = CRGB::Magenta;
      }

      for (int x = walls[y].second; x < display->size.x; x++) {
        display->Pixel(x, y) = CRGB::Magenta;
      }
    }

    // Draw player
    display->Pixel((int)player.location.x, (int)player.location.y) =
        CRGB::Green;
  }
};

}  // namespace falling
}  // namespace games
}  // namespace kss
