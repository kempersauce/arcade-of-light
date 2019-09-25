//    Shrapnel.h
//library for physics affected dots with a defineable Hue value

#include <Animation.h>

class FancyShrapnel : Animation
{
public:
    //location values
    PhysicsInfo physics;

    bool Burnout;
    long BirthTime;

    //colors (HSV)
    int Hue;

    /**
     * Firework Constructor
     * @param loc - location on LED strip
     * @param red - red value (0-255)
     * @param green - green value (0-255)
     * @param blue - blue value (0-255)
     * */
    FancyShrapnel()
        : Animation(),
        physics()
    {
        Hue = 0;
        Burnout = false;
        BirthTime = 0;
    }

    void Reset()
    {
        physics.Reset();
        Hue = 0;
        Burnout = false;
        BirthTime = millis();
    }

    void Move()
    {
        physics.Move();

        float timeDiff =  (float)(millis() - BirthTime) / 1000;

        if (timeDiff > 3.5)
        {
            Reset();
        }
    }

    void draw(Display* display)
    {
        if (physics.Location >= 0 && physics.Location < display->lengthStrips)
        {
            float timeDiff =  (float)(millis() - BirthTime) / 1000;

            // Saturate Color for 2 seconds
            int Saturation = min(255 * timeDiff / 2, 255);

            // Then fade to Black for the next 1.5 seconds
            int Brightness = min(max(255 - (255 * (timeDiff - 2) / 1.5), 0), 255);

            int middleStrip = display->numStrips / 2;
            display->strips[middleStrip][(int)physics.Location].setHSV(Hue, Saturation, Brightness);
        }
    }
};
