#include <Animation.h>
#include <FancyShrapnel.h>
#define NUM_SHRAPNEL 3

class FancyFirework : Animation
{
    public:
        //location values
        float Location;
        float Velocity;
        float Acceleration;
        FancyShrapnel shrapnel[5];

        int Height; //pixel height where the firework explodes
        int Speed; //pixels per second
        float ShrapnelSpeed;
        bool Exploded;
        bool ShrapnelSpawned;
        long BirthTime;
        long CurrentTime;
        long OldTime;

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
        FancyFirework()
        {
            Location = 0;
            Velocity = random8(1,25)/10;  //pixels per second (I hope)
            Height = random8(0,100)+150;
            Hue = random(0,255);
            Saturation = 0;
            Brightness = 255;
            Exploded = false;
            ShrapnelSpawned = false;
            ShrapnelSpeed = - NUM_SHRAPNEL / 2;
        }

        void Reset()
        {
          Location = 0;
          Velocity = random8(1,25)/10;  //pixels per second (I hope)
          Height = random8(0,100)+150;
          Hue = random(0,255);
          Saturation = 0;
          Brightness = 100;
          Exploded = false;
          ShrapnelSpawned = false;
          ShrapnelSpeed = - 1;
        }

        void Move()
        {
          if (CurrentTime - BirthTime > 5500){Reset();}
            if (Exploded == true)
              {
                //create fancy shrapnels here and pass hue & initial parameters
                if (ShrapnelSpawned == false){
                ShrapnelSpawned = true;
                for (int i = 0; i < NUM_SHRAPNEL; i++){
                  shrapnel[i].Location = Location;
                  shrapnel[i].Velocity = Velocity + ShrapnelSpeed/10;
                  shrapnel[i].Brightness = 255;
                  shrapnel[i].Hue = Hue;
                  shrapnel[i].BirthTime = millis();
                  ShrapnelSpeed += 1;
                  }
               }
                //check if fancy shrapnels are alive
                for (int i = 0; i < 5; i++){
                shrapnel[i].Move();
                  }
                }
            if (Exploded == false)
            {
                CurrentTime = millis();
                Location += Velocity;
                //Location += (OldTime - CurrentTime) * (Velocity/1000);
                if (Location >= Height)
                {
                    Exploded = true;
                }

              //Saturate Color
              if (Saturation < 255){
                Saturation = 255 * (Location / Height);
                }
          }
              OldTime = millis();
        }

        void draw(Display* display)
        {
          if (Exploded == false)
            {
              display->strips[display->numStrips/2][(int)Location].setHSV(Hue, Saturation, Brightness);
            }
            if (Exploded == true)
              {
          for (int i = 0; i < 5; i++){
            shrapnel[i].draw(display);
            }
          }
        }
};
