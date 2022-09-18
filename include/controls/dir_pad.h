
#pragma once

#include <PinSetup.h>

#include "controls/button.h"  // for Button

namespace kss {
namespace controls {

class DirPad {
 public:
  Button* up;
  Button* down;
  Button* left;
  Button* right;
  Button* a;
  Button* b;

  DirPad(Button* up, Button* down, Button* left, Button* right, Button* a,
         Button* b)
      : up{std::move(up)},        // pins::Buttons[4]
        down{std::move(down)},    // pins::Buttons[3]
        left{std::move(left)},    // pins::Buttons[5]
        right{std::move(right)},  // pins::Buttons[2]
        a{std::move(a)},          // pins::Buttons[1]
        b{std::move(b)}           // pins::Buttons[0]
  {}

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
