#pragma once

#include <map>     // For std::map
#include <memory>  // For std::shared_ptr

#include "controls/button.h"            // For Button
#include "controls/hardware/context.h"  // For Context
#include "controls/hardware/simple.h"   // For Simple

namespace kss {
namespace controls {
namespace hardware {

// A Matrix context is really just a series of Simple contexts that get polled
// efficiently
class Matrix : public Context {
 public:
  using InputMatrix = std::map<uint8_t, Simple>;

  std::shared_ptr<Button> CreateButton(uint8_t channel, uint8_t pin) {
    // Add the channel if it hasn't been registered yet
    auto channel_it = inputs_.find(channel);
    if (channel_it == inputs_.end()) {
      // Add the input channel and grab an iterator to it
      const auto emplace_result = inputs_.emplace(channel, Simple{LOW});
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
    for (auto channel_it = inputs_.begin(); channel_it != inputs_.end();
         channel_it++) {
      // Set the current channel to active and grab a reference to it
      SetActiveChannel(channel_it->first);
      channel_it->second.PollAll();
    }
  }

 private:
  // Using pin 0 as a dummy null pin
  uint8_t active_pin_{
      0};  // TODO - is there such a thing as pin 0? or should we revisit this?

  InputMatrix inputs_;

  // Switch to the appropriate pin (if we need to, avoiding extra switching)
  void SetActiveChannel(const uint8_t channel) {
    if (active_pin_ != channel) {
      // Set the old pin to Inactive (Hi)
      if (active_pin_ != 0) {
        digitalWriteFast(active_pin_, HIGH);
      }

      // Set the appropriate pin to Active (Lo)
      digitalWriteFast(channel, LOW);

      // Keep track of the current channel
      active_pin_ = channel;

      // Allow the signal to settle after switching channels
      delayMicroseconds(5);
    }
  }
};

}  // namespace hardware
}  // namespace controls
}  // namespace kss
