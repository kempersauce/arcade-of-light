/*
    Button Class
    creates an object that can read whether or not, and for how long the button is pressed
*/

#pragma once

namespace kss {
namespace controls {

class Button
{
public:

    Button() :
        was_pressed_{false},
        is_pressed_{false},

        frames_held_{0},
        hold_start_time_{0},

        frames_released_{1},
        released_start_time_{millis()}
    {
    }

    // Update the button state and some internals about it.
    // This gets called by whichever controls::hardware::Context created this button
    // each time through the game loop to keep the button state up-to-date
    void SetState(bool state) {
        // Save the old button state and record the new state
        was_pressed_ = is_pressed_;
        is_pressed_ = state;

        // Keep track of how long the button has been held
        if (IsDepressing())
        {
            // Record when the button went down
            // TODO reevaluate - do we want 0-based or 1-based frame counting like this?
            frames_held_ = 1; // We're counting the first frame here, so anything using this field can have an immediate response
            hold_start_time_ = millis();

            frames_released_ = 0;
            released_start_time_ = 0;
        }
        else if (IsHolding())
        {
            // Increment frames held, the time-based property doesn't need updating here
            frames_held_++;
        }
        else if (IsReleasing())
        {
            // Record when the button released
            frames_released_ = 1;
            released_start_time_ = millis();
        }
        else
        {
            // Clear hold state - this button was released in a previous frame
            frames_held_ = 0;
            hold_start_time_ = 0;

            // Increment frames released, the time-based property doesnt need updating here
            frames_released_++;
        }
    }



    // Detect current button state, doesn't take into account state change

    const bool IsPressed() {
        return is_pressed_;
    }

    const bool IsUp() {
        return !IsPressed();
    }



    // Detect button state changes, taking into account the previous button state

    const bool IsDepressing() {
        // Button depressed (released > pressed)
        return !was_pressed_ && is_pressed_;
    }

    const bool IsReleasing() {
        // Button released (pressed > released)
        return was_pressed_ && !is_pressed_;
    }

    const bool IsHolding() {
        // Button held (pressed > pressed)
        return was_pressed_ && is_pressed_;
    }



    // Detect how long the button has been pressed down

    // Returns the number of frames the button has been held down (starting with 1 at the depressing frame, not counting the release frame)
    // Returns 0 when the button isnt being held down at all
    const int GetFramesHeld() {
        return frames_held_;
    }

    // Returns the number of milliseconds since the button has become depressed
    // NOTE - this may vary if there is a lot of computation time between poll() and GetMillisHeld()
    const long GetMillisHeld() {
        // Return 0 if it's not being held
        if (hold_start_time_ == 0)
        {
            return 0;
        }
        else
        {
            return millis() - hold_start_time_;
        }
    }



    // Detect how long the button has been released

    // Returns the number of frames the button has been released (starting with 1 at the releasing frame, not counting the depressing frame)
    // Returns 0 when the button isnt being held down at all
    const int GetFramesReleased() {
        return frames_released_;
    }

    // Returns the number of milliseconds since the button has been released
    // NOTE - this may vary if there is a lot of computation time between poll() and GetMillisReleased()
    const long GetMillisReleased() {
        // Return 0 if it's not being held
        if (released_start_time_ == 0)
        {
            return 0;
        }
        else
        {
            return millis() - released_start_time_;
        }
    }

private:

    // Track button up/down state (false = released = up) (true = pressed = down)
    bool was_pressed_;
    bool is_pressed_;

    // Used to track how long the button has been held down
    // TODO maybe decide between doing it one way or the other? right now I'm doing both
    int frames_held_;
    long hold_start_time_;

    // Used to track how long since the button's been released
    int frames_released_;
    long released_start_time_;
};

}  // namespace kss::controls
}  // namespace kss
