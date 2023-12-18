#pragma once

#include <array>   // for std::array
#include <vector>  // for std::vector

#include "controls/button.h"  // for Button

namespace kss {
namespace controls {

template <size_t BUTTON_COUNT>
struct Controller {
  static constexpr size_t button_count{BUTTON_COUNT};
  std::array<Button*, BUTTON_COUNT> buttons;
  std::vector<Button*> exclude_from_idle;
  uint32_t idle_timeout_millis;

  Controller() : buttons{NULL}, idle_timeout_millis{0} {}
  Controller(std::array<Button*, BUTTON_COUNT> buttons,
             uint32_t idle_timeout_millis = 0)
      : buttons{buttons}, idle_timeout_millis{idle_timeout_millis} {}
  virtual ~Controller() = default;

  virtual bool IsIdle() {
    if (idle_timeout_millis == 0) {
      return false;
    }

    for (auto button : buttons) {
      if (button != NULL && button->GetMillisReleased() < idle_timeout_millis) {
        for (auto exclude : exclude_from_idle) {
          if (button == exclude) {
            continue;
          }
        }
        return false;
      }
    }
    return true;
  }

  virtual bool AnyDepressing() {
    for (auto button : buttons) {
      if (button != NULL && button->IsDepressing()) {
        return true;
      }
    }
    return false;
  }

  virtual bool AnyHolding() {
    for (auto button : buttons) {
      if (button != NULL && button->IsHolding()) {
        return true;
      }
    }
    return false;
  }
};

}  // namespace controls
}  // namespace kss
