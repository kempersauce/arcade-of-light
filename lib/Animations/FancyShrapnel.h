//    Shrapnel.h
//library for physics affected dots with a defineable Hue value

#include <Animation.h>

class FancyShrapnel : Animation
{
public:
    //location values
    float Location;
    float Velocity;

    bool Burnout;
    long BirthTime;
    long CurrentTime;

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
        BirthTime = 0;
    }

    void Reset()
    {
      Location = 0;
      Velocity = 0;
      Hue = 0;
      Saturation = 0;
      Brightness = 0;
      Burnout = false;
      BirthTime = 0;
    }

    void Move()
    {
        CurrentTime = millis();
        Velocity += 1/10;//decay velocity due to "Gravity"
        Location += Velocity;
        if (Location < 0){Location = 0;}
        if (Location > 255){Location = 255;}
        //Saturate Color
        if (Saturation < 255){
          Saturation = 255 * ((CurrentTime - BirthTime / 2000));
          if (Saturation > 255){Saturation = 255;}
          }
        //Fade to Black
        if (Saturation == 255){
          Brightness = 255 - (255 * ((CurrentTime - BirthTime / 3500)));

          }
        if (CurrentTime - BirthTime > 3500){Burnout = true;}
        if (Burnout == true){Reset();}
      }

    void draw(Display* display)
    {
      display->strips[display->numStrips/2][(int)Location].setHSV(Hue, Saturation, Brightness);
    }
};
