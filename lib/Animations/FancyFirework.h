#include <Animation.h>
#include <FancyShrapnel.h>
#define NUM_SHRAPNEL 14

class FancyFirework : Animation
{
public:
    //location values
    PhysicsInfo physics;

    FancyShrapnel shrapnel[NUM_SHRAPNEL];

    bool ShrapnelSpawned;
    long BirthTime;

    //colors (HSV)
    int Hue;
    int Saturation;
    int Brightness;

    int StripHeight;

    /**
     * Firework Constructor
     * @param loc - location on LED strip
     * @param red - red value (0-255)
     * @param green - green value (0-255)
     * @param blue - blue value (0-255)
     * */
    FancyFirework(int stripLength)
        : Animation(),
        physics()
    {
        StripHeight = stripLength;
        physics.ExplodeVelocity = 0;// explode on contact
        Reset();

        Hue = random(0, 255);
        Saturation = 0;
        Brightness = 255;
        ShrapnelSpawned = false;
    }

    void Reset()
    {
        physics.Reset();
        physics.LocationMax = random8(StripHeight / 3, StripHeight - 20); // height the firework explodes
        physics.Velocity = random8(50, 70);
        BirthTime = millis();

        Hue = random(0, 255);
        Saturation = 0;
        Brightness = 100;
        ShrapnelSpawned = false;
    }

    void Move()
    {
        if (millis() - BirthTime > 5500)
        {
            Reset();
        }

        physics.Move();

        if (physics.HasExploded)
        {
            //create fancy shrapnels here and pass hue & initial parameters
            if (ShrapnelSpawned == false)
            {
                ShrapnelSpawned = true;
                for (int i = 0; i < NUM_SHRAPNEL; i++)
                {
                    shrapnel[i].physics.Reset();
                    shrapnel[i].physics.Location = physics.Location;
                    shrapnel[i].physics.Velocity = (((float)random16() / (float)UINT16_MAX) - .5) * 150;
                    shrapnel[i].Hue = Hue;
                    shrapnel[i].BirthTime = millis();
                }
            }

            //check if fancy shrapnels are alive
            for (int i = 0; i < NUM_SHRAPNEL; i++)
            {
                shrapnel[i].physics.Velocity *= .9;
                shrapnel[i].Move();
            }
        }
        else
        {
            //Saturate Color
            if (Saturation < 255)
            {
                Saturation = 255 * (physics.Location / physics.LocationMax);
            }
        }
    }

    void draw(Display* display)
    {
        if (physics.HasExploded == false)
        {
            int midStrip = display->numStrips / 2;
            display->strips[midStrip][(int)physics.Location].setHSV(Hue, Saturation, Brightness);
        }
        else
        {
            for (int i = 0; i < NUM_SHRAPNEL; i++)
            {
                shrapnel[i].draw(display);
            }
        }
    }
};
