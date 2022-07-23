
#pragma once

#include <PinSetup.h>
#include <button.h>  // For Button

#include <memory>  // For shared_ptr

namespace kss {
namespace controls {

class DirPad {
 public:
  std::shared_ptr<Button> up;
  std::shared_ptr<Button> down;
  std::shared_ptr<Button> left;
  std::shared_ptr<Button> right;
  std::shared_ptr<Button> a;
  std::shared_ptr<Button> b;

  DirPad(std::shared_ptr<Button> up, std::shared_ptr<Button> down,
         std::shared_ptr<Button> left, std::shared_ptr<Button> right,
         std::shared_ptr<Button> a, std::shared_ptr<Button> b)
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
