#include <map>

namespace controls::matrix {

class Context {

  // TODO replace InputState with a reference to the actual button (or its state member)
  // Alternatively, each button needs to poll their actual state from here instead of from digitalRead(..)
  // Probably the latter option is the best, and Buttons should always poll from a ButtonStateProvider or something
  using InputState = bool;
  using InputChannel = std::map<uint8_t, InputState>;
  using InputMatrix = std::map<uint8_t, InputChannel>;

 public:
  void RegisterInput(const uint8_t channel_in, const uint8_t channel_out) {
    // Add the channel if it hasn't been registered yet
    auto channel_it = input_matrix.find(channel_in);
    if (channel_it == input_matrix.end()) {
      // Add the channel and grab an iterator to it
      channel_it = input_matrix.emplace(channel_in, InputChannel{}).first;

      // Set this new channel inactive for the time being
      digitalWrite(channel_in, HIGH);
    }

    // Register the state with the output channel (second entry in the map iterator pair)
    channel_it->second.emplace(channel_out, false);
  }

  void PollAll() {
    for (auto channel_it = input_matrix.begin(); channel_it != input_matrix.end(); channel_it++) {
      // Set the current channel to active and grab a reference to it
      SetActiveChannel(channel_it->first);
      auto& channel = channel_it->second;

      // Loop through registered inputs for this channel and update their in-memory state
      for (auto input_it = channel.begin(); input_it != channel.end(); input_it++) {
        input_it->second = digitalRead(input_it->first) == 1;
      }
    }
  }

  const bool GetState(const uint8_t channel, const uint8_t input) {
    return input_matrix.at(channel).at(input);
  }

 private:
  // Using pin 0 as a dummy null pin
  uint8_t active_pin_{0};  // TODO - is there such a thing as pin 0? or should we revisit this?

  InputMatrix input_matrix;

  // Switch to the appropriate pin (if we need to, avoiding extra switching)
  void SetActiveChannel(const uint8_t channel) {
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
}

} // namespace controls::matrix