#include "controls/hardware/simple.h"

#include <memory>  // For shared_ptr, make_shared

namespace controls::hardware {

std::shared_ptr<Button> Simple::CreateButton(uint8_t pin, uint8_t unused) {
    // Register this pin out on the input channel, and set that pin as INPUT
    const auto result = inputs_.emplace(pin, std::make_shared<Button>());
    if (result.second) {
        pinMode(pin, INPUT);
    }

    return *result.first;
}

void Simple::PollAll() {
    // Loop through registered inputs and update their in-memory state
    for (auto input_it = inputs_.begin(); input_it != inputs_.end(); input_it++) {
        const auto state = digitalRead(input_it->first) == 1;
        input_it->second->SetState(state);
    }
}

}  // namespace controls::hardware
