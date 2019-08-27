//    Shrapnel.h
//library for physics affected dots with a defineable Hue value

#include <Animation.h>

class Shrapnel : Animation
public:
    //location values
    Float Loc;
    Float Velocity;
    Float Acceleration;
    Float OldVelocity;
    Float OldAcceleration;

    bool Exploded;
    long BirthTime;
    long CurrentTime;

    int Thrust;

    //colors (HSV)
    int Hue;
    int Saturation;
    int Brightness;

    /**
     * Firework Constructor
     * @param loc - location on LED strip
     * @param red - red value (0-255)
     * @param green - green value (0-255)
     * @param blue - blue value (0-255)
     * */
    Shrapnel()
        : Animation()
    {
        Loc = 0;
        Velocity = 0;
        Hue = random(0,255);
        Saturation = 0;
        Brightness = 255;
        Exploded = false;
        BirthTime = millis();
        Thrust = random(1,150);
    }

    void Move()
    {

        CurrentTime = millis();

        //Equations
        Acceleration = ( .5 * (Thrust + oldThrust))/ Mass - GRAVITY;
        Velocity = OldVelocity + ((CurrentTime - BirthTime)/1000) * Acceleration;
        Location = OldLocation + (.5 * (Velocity + OldVelocity)) * ((CurrentTime - BirthTime)/1000);

        OldVelocity = Velocity;
        OldLocation = Location;

        //Saturate Color
        if (Saturation < 256){
          Saturation = Saturation + 20;

      }

    }

    void Reset()
    {
        Loc = 0;
        //Location = 0;
        Speed = random8(1,5)+10;
        Height = random8(0,250)+50;
        Hue = random(0,255);
        Saturation = 0;
        Brightness = 255;
        Exploded = false;

    }

    void draw(Display* display)
    {
      display->strips[(int)Loc] = CHSV(Hue, Saturation, Brightness)
    }
};
