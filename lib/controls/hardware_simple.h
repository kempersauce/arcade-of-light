#pragma once

#include <map>  // For std::map
#include <memory>  // For std::shared_ptr

#include <hardware_context.h>  // For Context
#include <button.h>  // For Button

namespace kss {
namespace controls {
namespace hardware {

class Simple : public Context {
  public:
  
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
        for (auto input_it = inputs_.begin(); input_it != inputs_.end(); input_it++) {
            const auto state = digitalRead(input_it->first) == 1;
            input_it->second->SetState(state);
        }
    }

  private:
    InputMap inputs_;
};

}  // namespace kss::controls::hardware
}  // namespace kss::controls
}  // namesapce kss
