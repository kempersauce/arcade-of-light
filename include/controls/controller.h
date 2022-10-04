#pragma once

#include <array>  // for std::array

#include "controls/button.h"  // for Button

namespace kss {
namespace controls {

template <size_t BUTTON_COUNT>
struct Controller {
  static constexpr size_t button_count{BUTTON_COUNT};
  std::array<Button*, BUTTON_COUNT> buttons;
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
};

}  // namespace controls
}  // namespace kss
