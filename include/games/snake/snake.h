
#pragma once

#include <deque>    // for deque
#include <utility>  // for pair

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace games {
namespace snake {

enum Direction { Up, Down, Left, Right };

class Snake : public animation::Animation {
 public:
  int xMax;
  int yMax;

  std::pair<int, int> head;
  std::deque<std::pair<int, int>> body;
  int lengthToGrow;

  CRGB color;

  Direction currentDirection;

  Snake(int height, int width) : Animation(), head(), body() {
    color = CRGB::Green;
    xMax = height;
    yMax = width;
  }

  void Reset() {
    // clear out the body
    body.clear();

    head.first = xMax / 2;
    head.second = yMax / 2;
    currentDirection = Up;
    lengthToGrow = 6;
  }

  void Grow(int growth = 1) { lengthToGrow += growth; }

  void Move() {
    // If we have more to grow, do so by just not removing the tail end
    if (lengthToGrow > 0) {
      lengthToGrow--;
    } else {
      body.pop_back();
    }

    // Add head's location to the beginning of the body
    body.push_front(head);

    // Create the new head according to our direction
    switch (currentDirection) {
      case Up:
        head = std::make_pair(head.first, (head.second + 1) % yMax);
        break;

      case Down:
        head = std::make_pair(head.first, (head.second - 1 + yMax) % yMax);
        break;

      case Left:
        head = std::make_pair((head.first - 1 + xMax) % xMax, head.second);
        break;

      case Right:
        head = std::make_pair((head.first + 1) % xMax, head.second);
        break;
    }
  }

  void draw(display::Display* display) {
    display->strips[head.first][head.second] = color;
    for (int i = 0; i < body.size(); i++) {
      display->strips[body[i].first][body[i].second] = color;
    }
  }
};

}  // namespace snake
}  // namespace games
}  // namespace kss
