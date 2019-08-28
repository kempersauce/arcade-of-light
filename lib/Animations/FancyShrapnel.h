//    Shrapnel.h
//library for physics affected dots with a defineable Hue value

#include <Animation.h>

class FancyShrapnel : Animation
{
public:
    //location values
    float Location;
    float OldLocation;
    float Velocity;
    float Acceleration;
    float OldVelocity;
    float OldAcceleration;

    int Mass;

    bool Burnout;
    long BirthTime;
    long CurrentTime;

    int Thrust;
    int OldThrust;

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
    FancyShrapnel()
    //: Animation(),
    {
        Location = 0;
        Velocity = 0;
        Hue = 0;
        Saturation = 0;
        Brightness = 0;
        Burnout = false;
        BirthTime = millis();
        Thrust = random(1,150);
        OldThrust = 0;
        Mass = 1;
    }

    void Move()
    {

        CurrentTime = millis();

        //Equations
        Acceleration = ( .5 * (Thrust + OldThrust))/ Mass - GRAVITY;
        Velocity = OldVelocity + ((CurrentTime - BirthTime)/1000) * Acceleration;
        Location = OldLocation + (.5 * (Velocity + OldVelocity)) * ((CurrentTime - BirthTime)/1000);

        OldVelocity = Velocity;
        OldLocation = Location;

        //Saturate Color
        if (Saturation < 255){
          Saturation = Saturation + 20;

      }
    }

    void draw(Display* display)
    {
      display->strips[display->numStrips/2][(int)Location].setHSV(Hue, Saturation, Brightness);
    }
};
