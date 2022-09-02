#pragma once

/*
        Button Class
        Tracks whether or not, and for how long the button is pressed
*/

namespace kss {
namespace controls {

class Button {
  // Track button up/down state (false = released = up) (true = pressed = down)
  bool was_pressed{false};
  bool is_pressed{false};

  // Used to track how long the button has been held down
  int frames_held{0};
  uint32_t hold_start_time{0};

  // Used to track how long since the button's been released
  int frames_released{1};
  uint32_t released_start_time{millis()};

 public:
  // Update the button state and some internals about it.
  // This gets called by whichever controls::hardware::Context created this
  // button each time through the game loop to keep the button state up-to-date
  void SetState(bool state) {
    // Save the old button state and record the new state
    was_pressed = is_pressed;
    is_pressed = state;

    // Keep track of how long the button has been held
    if (IsDepressing()) {
      // Record when the button went down
      frames_held = 1;  // We're counting the first frame here, so anything
                        // using this field can have an immediate response
      hold_start_time = millis();

      frames_released = 0;
      released_start_time = 0;
    } else if (IsHolding()) {
      // Increment frames held, the time-based property doesn't need updating
      // here
      frames_held++;
    } else if (IsReleasing()) {
      // Record when the button released
      frames_released = 1;
      released_start_time = millis();
    } else {
      // Clear hold state - this button was released in a previous frame
      frames_held = 0;
      hold_start_time = 0;

      // Increment frames released, the time-based property doesnt need updating
      // here
      frames_released++;
    }
  }

  // Detect current button state, doesn't take into account state change

  bool IsPressed() const { return is_pressed; }

  bool IsUp() const { return !IsPressed(); }

  // Detect button state changes, taking into account the previous button state

  bool IsDepressing() const {
    // Button depressed (released > pressed)
    return !was_pressed && is_pressed;
  }

  bool IsReleasing() const {
    // Button released (pressed > released)
    return was_pressed && !is_pressed;
  }

  bool IsHolding() const {
    // Button held (pressed > pressed)
    return was_pressed && is_pressed;
  }

  // Detect how long the button has been pressed down

  // Returns the number of frames the button has been held down (starting with 1
  // at the depressing frame, not counting the release frame) Returns 0 when the
  // button isnt being held down at all
  int GetFramesHeld() const { return frames_held; }

  // Returns the number of milliseconds since the button has become depressed
  // NOTE - this may vary if there is a lot of computation time between poll()
  // and GetMillisHeld()
  uint32_t GetMillisHeld() const {
    // Return 0 if it's not being held
    if (hold_start_time == 0) {
      return 0;
    } else {
      return millis() - hold_start_time;
    }
  }

  // Detect how long the button has been released

  // Returns the number of frames the button has been released (starting with 1
  // at the releasing frame, not counting the depressing frame) Returns 0 when
  // the button isnt being held down at all
  int GetFramesReleased() const { return frames_released; }

  // Returns the number of milliseconds since the button has been released
  // NOTE - this may vary if there is a lot of computation time between poll()
  // and GetMillisReleased()
  uint32_t GetMillisReleased() const {
    // Return 0 if it's not being held
    if (released_start_time == 0) {
      return 0;
    } else {
      return millis() - released_start_time;
    }
  }
};

}  // namespace controls
}  // namespace kss
