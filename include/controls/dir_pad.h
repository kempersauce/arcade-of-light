
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
      : up{std::move(up)},        // BUTTON_PIN_4
        down{std::move(down)},    // BUTTON_PIN_3
        left{std::move(left)},    // BUTTON_PIN_5
        right{std::move(right)},  // BUTTON_PIN_2
        a{std::move(a)},          // BUTTON_PIN_1
        b{std::move(b)}           // BUTTON_PIN_0
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
