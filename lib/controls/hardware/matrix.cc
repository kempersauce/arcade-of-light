#include "controls/hardware/matrix.h"

#include <memory>  // For shared_ptr, make_shared

namespace controls::hardware {

std::shared_ptr<Button> Matrix::CreateButton(uint8_t channel, uint8_t pin) {
    // Add the channel if it hasn't been registered yet
    auto channel_it = inputs_.find(channel);
    if (channel_it == inputs_.end()) {
        // Add the input channel and grab an iterator to it
        const auto emplace_result = inputs_.emplace(channel, InputChannel{});
        channel_it = emplace_result.first;

        // If this is a new channel, set it inactive initially
        if (emplace_result.second) {
            digitalWrite(channel, HIGH);
        }
    }

    // Register this pin out on the input channel, and set that pin as INPUT
    const auto result = channel_it->second.emplace(pin, std::make_shared<Button>());
    if (result.second) {
        pinMode(pin, INPUT);
    }

    return *result.first;
}

void Matrix::PollAll() {
    for (auto channel_it = inputs_.begin(); channel_it != inputs_.end(); channel_it++) {
        // Set the current channel to active and grab a reference to it
        SetActiveChannel(channel_it->first);
        auto& channel = channel_it->second;

        // Loop through registered inputs for this channel and update their in-memory state
        for (auto input_it = channel.begin(); input_it != channel.end(); input_it++) {
            const auto state = digitalRead(input_it->first) == 1;
            input_it->second->SetState(state);
        }
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
