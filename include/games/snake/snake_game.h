#pragma once

#include "animation/single_color_background.h"  // for SingleColorBG
#include "controls/dir_pad.h"                   // for DirPad
#include "games/game.h"                         // for Game
#include "games/snake/snake.h"                  // for Snake

namespace kss {
namespace games {
namespace snake {

class SnakeGame : public Game {
  controls::DirPad controls;
  Snake snake;
  animation::SingleColorBG background;

 public:
  SnakeGame(display::Display* gameDisplay, controls::DirPad controls)
      : Game(gameDisplay),
        controls{std::move(controls)},
        snake{gameDisplay->size.x, gameDisplay->size.y},
        background{CRGB::Black} {}

  void setup() override { snake.Reset(); }

  void loop() override {
    if (controls.up->IsDepressing() && snake.currentDirection != Down) {
      snake.currentDirection = Up;
    } else if (controls.down->IsDepressing() && snake.currentDirection != Up) {
      snake.currentDirection = Down;
    } else if (controls.left->IsDepressing() &&
               snake.currentDirection != Right) {
      snake.currentDirection = Left;
    } else if (controls.right->IsDepressing() &&
               snake.currentDirection != Left) {
      snake.currentDirection = Right;
    }

    if (controls.a->IsPressed()) {
      snake.Grow();
    }

    snake.Move();

    if (snake.head.first < 0 || snake.head.first >= display->size.x ||
        snake.head.second < 0 || snake.head.second >= display->size.y) {
      setup();
    }

    background.draw(display);
    snake.draw(display);
  }
};

}  // namespace snake
}  // namespace games
}  // namespace kss
