#pragma once

#include <button.h>            // For Button
#include <hardware_context.h>  // For Context

#include <map>     // For std::map
#include <memory>  // For std::shared_ptr

namespace kss {
namespace controls {
namespace hardware {

class Simple : public Context {
 public:
  Simple(uint8_t pressed_signal = HIGH) : pressed_signal_{pressed_signal} {}

  using InputMap = std::map<uint8_t, std::shared_ptr<Button>>;

  std::shared_ptr<Button> CreateButton(uint8_t pin) {
    // Register this pin out on the input channel, and set that pin as INPUT
    const auto result = inputs_.emplace(pin, std::make_shared<Button>());
    if (result.second) {
      pinMode(pin, INPUT);
    }

    return result.first->second;
  }

  void PollAll() override {
    // Loop through registered inputs and update their in-memory state
    for (auto input_it = inputs_.begin(); input_it != inputs_.end();
         input_it++) {
      const auto state = digitalRead(input_it->first) == pressed_signal_;
      input_it->second->SetState(state);
    }
  }

 private:
  const uint8_t pressed_signal_;
  InputMap inputs_;
};

}  // namespace hardware
}  // namespace controls
}  // namespace kss
