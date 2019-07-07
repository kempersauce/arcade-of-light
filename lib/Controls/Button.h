/* 
    Button Class
    creates an object that can read whether or not, and for how long the button is pressed
*/
class Button {
    //Arduino pin button is connected to
    const int _pin;

    // Track button up/down state (false = released = up) (true = pressed = down)
    bool _wasPressed;
    bool _isPressed;

    // Used to track how long the button has been held down
    // TODO maybe decide between doing it one way or the other? right now I'm doing both
    int framesHeld;
    long holdStartTime;

public:
    //Constructor - takes a pinNumber to poll button state from
    Button(int pinNo) : _pin(pinNo)
    {
        pinMode(_pin, INPUT);

        // Initialize internal state members
        _wasPressed = false;
        _isPressed = false;
        framesHeld = 0;
        holdStartTime = 0;

        // Poll now to set the backlog - this ensures we have the correct button state when we start
        poll();
    }

    // Poll the switch state and update some internals about it.
    // This needs to be called each time through the game loop to keep the button state up-to-date
    void poll()
    {
        // Save the old button state and record the new state
        _wasPressed = _isPressed;
        _isPressed = digitalRead(_pin) == 1;

        // Keep track of how long the button has been held
        if (isDepressing())
        {
            // Record when the button went down
            // TODO reevaluate - do we want 0-based or 1-based frame counting like this?
            framesHeld = 1; // We're counting the first frame here, so anything using this field can have an immediate response
            holdStartTime = millis();
        }
        else if (isHolding())
        {
            // Increment frames held, the time-based property doesn't need updating here
            framesHeld++;
        }
        else if (isReleasing())
        {
            // Nothing to do here, both frame-based and time-based properties are accurate
        }
        else
        {
            // Clear hold state - this button was released in a previous frame
            framesHeld = 0;
            holdStartTime = 0;
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
};
