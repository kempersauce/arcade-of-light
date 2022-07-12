#include "controls/hardware/matrix.h"

#include <memory>  // For shared_ptr, make_shared

#include "controls/hardware/simple.h"  // For Simple

namespace controls::hardware {

std::shared_ptr<Button> Matrix::CreateButton(uint8_t channel, uint8_t pin) {
    // Add the channel if it hasn't been registered yet
    auto channel_it = inputs_.find(channel);
    if (channel_it == inputs_.end()) {
        // Add the input channel and grab an iterator to it
        const auto emplace_result = inputs_.emplace(channel, Simple{});
        channel_it = emplace_result.first;

        // If this is a new channel, set it inactive initially
        if (emplace_result.second) {
            digitalWrite(channel, HIGH);
        }
    }

    // Create a button on the channel
    return channel_it->second.CreateButton(pin);
}

void Matrix::PollAll() {
    for (auto channel_it = inputs_.begin(); channel_it != inputs_.end(); channel_it++) {
        // Set the current channel to active and grab a reference to it
        SetActiveChannel(channel_it->first);
        channel_it->second.PollAll();
    }
}

void Matrix::SetActiveChannel(uint8_t channel) {
    if (active_pin_ != channel) {

        // Set the old pin to Inactive (Hi)
        if (active_pin_ != 0) {
            digitalWrite(active_pin_, HIGH);
        }

        // Set the appropriate pin to Active (Lo)
        digitalWrite(channel, LOW);

        // Keep track of the current channel
        active_pin_ = channel;
    }
}

}  // namespace controls::hardware
