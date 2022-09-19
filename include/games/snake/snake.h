
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
  size_t xMax;
  size_t yMax;

  std::pair<size_t, size_t> head;
  std::deque<std::pair<size_t, size_t>> body;
  size_t lengthToGrow;

  CRGB color;

  Direction currentDirection;

  Snake(size_t height, size_t width)
      : Animation(), xMax{height}, yMax{width}, head(), body() {
    color = CRGB::Green;
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

  virtual void Move() override {
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
    display->Pixel(head.first, head.second) = color;
    for (size_t i = 0; i < body.size(); i++) {
      display->Pixel(body[i].first, body[i].second) = color;
    }
  }
};

}  // namespace snake
}  // namespace games
}  // namespace kss
