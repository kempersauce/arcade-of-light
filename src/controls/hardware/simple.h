#pragma once

#include <map>  // for std::map

#include "controls/button.h"            // for Button
#include "controls/hardware/context.h"  // for Context

namespace kss {
namespace controls {
namespace hardware {

class Simple : public Context {
  const uint8_t pressed_signal;

  std::map<uint8_t, Button*> inputs;

 public:
  Simple(uint8_t pressed_signal = HIGH) : pressed_signal{pressed_signal} {}

  Button* CreateButton(uint8_t pin) {
    // Register this pin out on the input channel, and set that pin as INPUT
    const auto& result = inputs.emplace(pin, new Button());
    if (result.second) {
      pinMode(pin, INPUT);
    }

    return result.first->second;
  }

  void PollAll() override {
    // Loop through registered inputs and update their in-memory state
    for (auto& input : inputs) {
      const auto state = digitalRead(input.first) == pressed_signal;
      input.second->SetState(state);
    }
  }
};

}  // namespace hardware
}  // namespace controls
}  // namespace kss
