
#pragma once

#include <deque>    // for deque
#include <utility>  // for pair

#include "animation/single_color_background.h"  // for SingleColorBG
#include "controls/dir_pad.h"                   // for DirPad
#include "engines/physics_info.h"               // for PhysicsInfo
#include "engines/random.h"                     // for random::*
#include "games/game.h"                         // for Game

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
      : Game(gameDisplay),
        controls{std::move(controls)},
        player(),
        background(0, 0, 0),
        walls() {}

  virtual void setup() {
    player.xLocation = display->strip_count / 2;
    player.Location = display->strip_length * 2 / 3;

    // seed walls with initial stuff
    walls.clear();
    while (walls.size() < display->strip_length - 1) {
      walls.push_front(std::make_pair(-1, display->strip_count));
    }
  }

  void addWalls() {
    int left;
    int right;
    do {
      left = walls.front().first + engines::random::Int8_incl(-1, 1);
      right = walls.front().second + engines::random::Int8_incl(-1, 1);

      // Prevent the random walk from going more than 1 outside the visible
      // range
      if (left < -1) left = -1;

      if (right > display->strip_count) right = display->strip_count;

      // TODO check if left < right

      // Cap this at 2 pixel width tunnel
    } while (right - left < (display->strip_count + 1) / 2);

    walls.pop_back();
    walls.push_front(std::make_pair(left, right));
  }

  virtual void loop() {
    if (controls.up->IsPressed()) {
      player.Velocity = 10;
    } else if (controls.down->IsPressed()) {
      player.Velocity = -10;
    } else {
      player.Velocity = 0;
    }

    if (controls.left->IsPressed()) {
      player.xVelocity = -10;
    } else if (controls.right->IsPressed()) {
      player.xVelocity = 10;
    } else {
      player.xVelocity = 0;
    }

    player.Move();
    if (player.Location < 0)
      player.Location = 0;
    else if (player.Location >= display->strip_length)
      player.Location = display->strip_length - 1;

    if (player.xLocation < 0)
      player.xLocation = 0;
    else if (player.xLocation >= display->strip_count)
      player.xLocation = display->strip_count - 1;

    addWalls();

    if (player.xLocation <= walls[(int)player.Location].first ||
        player.xLocation >= walls[(int)player.Location].second) {
      setup();
    }

    background.draw(display);

    // draw the walls
    for (int y = 0; y < display->strip_length; y++) {
      for (int x = 0; x <= walls[y].first; x++) {
        display->Pixel(x, y) = CRGB::Magenta;
      }

      for (int x = walls[y].second; x < display->strip_count; x++) {
        display->Pixel(x, y) = CRGB::Magenta;
      }
    }

    // draw player
    display->Pixel((int)player.xLocation, (int)player.Location) = CRGB::Green;
  }
};

}  // namespace falling
}  // namespace games
}  // namespace kss
