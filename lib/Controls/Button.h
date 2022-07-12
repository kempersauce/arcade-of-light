/*
    Button Class
    creates an object that can read whether or not, and for how long the button is pressed
*/

#pragma once

class Button
{
    // Track button up/down state (false = released = up) (true = pressed = down)
    bool _wasPressed;
    bool _isPressed;

    // Used to track how long the button has been held down
    // TODO maybe decide between doing it one way or the other? right now I'm doing both
    int framesHeld;
    long holdStartTime;

    // Used to track how long since the button's been released
    int framesReleased;
    long releasedStartTime;

public:
    Button()
    {
        // Initialize internal state members
        _wasPressed = false;
        _isPressed = false;

        framesHeld = 0;
        holdStartTime = 0;

        framesReleased = 1;
        releasedStartTime = millis();
    }

    // Poll the switch state and update some internals about it.
    // This needs to be called each time through the game loop to keep the button state up-to-date
    void SetState(bool state)
    {
        // Save the old button state and record the new state
        _wasPressed = _isPressed;
        _isPressed = state;

        // Keep track of how long the button has been held
        if (isDepressing())
        {
            // Record when the button went down
            // TODO reevaluate - do we want 0-based or 1-based frame counting like this?
            framesHeld = 1; // We're counting the first frame here, so anything using this field can have an immediate response
            holdStartTime = millis();

            framesReleased = 0;
            releasedStartTime = 0;
        }
        else if (isHolding())
        {
            // Increment frames held, the time-based property doesn't need updating here
            framesHeld++;
        }
        else if (isReleasing())
        {
            // Record when the button released
            framesReleased = 1;
            releasedStartTime = millis();
        }
        else
        {
            // Clear hold state - this button was released in a previous frame
            framesHeld = 0;
            holdStartTime = 0;

            // Increment frames released, the time-based property doesnt need updating here
            framesReleased++;
        }
    }



    // Detect current button state, doesn't take into account state change

    bool isPressed()
    {
        return _isPressed;
    }

    bool isUp()
    {
        return !isPressed();
    }



    // Detect button state changes, taking into account the previous button state

    bool isDepressing()
    {
        // Button depressed (released > pressed)
        return !_wasPressed && _isPressed;
    }

    bool isReleasing()
    {
        // Button released (pressed > released)
        return _wasPressed && !_isPressed;
    }

    bool isHolding()
    {
        // Button held (pressed > pressed)
        return _wasPressed && _isPressed;
    }



    // Detect how long the button has been pressed down

    // Returns the number of frames the button has been held down (starting with 1 at the depressing frame, not counting the release frame)
    // Returns 0 when the button isnt being held down at all
    int getFramesHeld()
    {
        return framesHeld;
    }

    // Returns the number of milliseconds since the button has become depressed
    // NOTE - this may vary if there is a lot of computation time between poll() and getMillisHeld()
    long getMillisHeld()
    {
        // Return 0 if it's not being held
        if (holdStartTime == 0)
        {
            return 0;
        }
        else
        {
            return millis() - holdStartTime;
        }
    }



    // Detect how long the button has been released

    // Returns the number of frames the button has been released (starting with 1 at the releasing frame, not counting the depressing frame)
    // Returns 0 when the button isnt being held down at all
    int getFramesReleased()
    {
        return framesReleased;
    }

    // Returns the number of milliseconds since the button has been released
    // NOTE - this may vary if there is a lot of computation time between poll() and getMillisReleased()
    long getMillisReleased()
    {
        // Return 0 if it's not being held
        if (releasedStartTime == 0)
        {
            return 0;
        }
        else
        {
            return millis() - releasedStartTime;
        }
    }
};
