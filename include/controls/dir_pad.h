
#pragma once

#include "controls/button.h"  // for Button
#include "pins/pin_setup.h"

namespace kss {
namespace controls {

struct DirPad {
  static constexpr size_t button_count{6};
  union {
    struct {
      Button* up;
      Button* right;
      Button* left;
      Button* down;
      Button* a;
      Button* b;
    };
    Button* buttons[button_count];
  };

  DirPad(Button* up, Button* down, Button* left, Button* right, Button* a,
         Button* b)
      : up{up}, right{right}, left{left}, down{down}, a{a}, b{b} {}

  bool isIdle(uint32_t idleTimeout) {
    return up->GetMillisReleased() >= idleTimeout &&
           down->GetMillisReleased() >= idleTimeout &&
           left->GetMillisReleased() >= idleTimeout &&
           right->GetMillisReleased() >= idleTimeout &&
           a->GetMillisReleased() >= idleTimeout &&
           b->GetMillisReleased() >= idleTimeout;
  }
};

}  // namespace controls
}  // namespace kss
