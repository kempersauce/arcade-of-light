#pragma once

#include <map>  // for std::map

#include "controls/button.h"            // for Button
#include "controls/hardware/context.h"  // for Context
#include "controls/hardware/simple.h"   // for Simple

namespace kss {
namespace controls {
namespace hardware {

namespace _matrix {

constexpr uint8_t kUnusedPin{255};

}  // namespace _matrix

// A Matrix context is a series of Simple contexts that get polled efficiently
class Matrix : public Context {
  uint8_t active_pin{_matrix::kUnusedPin};

  std::map<uint8_t, Simple> inputs;

 public:
  Button* CreateButton(uint8_t channel, uint8_t pin) {
    // Add the channel if it hasn't been registered yet
    auto channel_it = inputs.find(channel);
    if (channel_it == inputs.end()) {
      // Add the input channel and grab an iterator to it
      auto emplace_result = inputs.emplace(channel, Simple{LOW});
      channel_it = emplace_result.first;

      // If this is a new channel, set it inactive initially
      if (emplace_result.second) {
        pinMode(channel, OUTPUT);
        digitalWriteFast(channel, HIGH);
      }
    }

    // Create a button on the channel
    return channel_it->second.CreateButton(pin);
  }

  void PollAll() override {
    for (auto& channel : inputs) {
      // Set the current channel to active and grab a reference to it
      SetActiveChannel(channel.first);
      channel.second.PollAll();
    }
  }

 private:
  // Switch to the appropriate pin (if we need to, avoiding extra switching)
  void SetActiveChannel(const uint8_t channel) {
    if (active_pin != channel) {
      // Set the old pin to Inactive (Hi)
      if (active_pin != _matrix::kUnusedPin) {
        digitalWriteFast(active_pin, HIGH);
      }

      // Set the appropriate pin to Active (Lo)
      digitalWriteFast(channel, LOW);

      // Keep track of the current channel
      active_pin = channel;

      // Allow the signal to settle after switching channels
      delayMicroseconds(5);
    }
  }
};

}  // namespace hardware
}  // namespace controls
}  // namespace kss
