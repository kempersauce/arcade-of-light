#include <Animation.h>
#include <FancyShrapnel.h>

class FancyFirework : Animation
{
    public:
        //location values
        float Location;
        float Velocity;
        float initialVelocity;
        float Acceleration;
        FancyShrapnel shrapnel[5];

        int Height; //pixel height where the firework explodes
        int Mass;
        int Speed; //pixels per second
        bool Exploded;
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
        FancyFirework()
        {
            Location = 0;
            Velocity = random8(1,5);
            Height = random8(0,100)+150;
            Hue = random(0,255);
            Saturation = 0;
            Brightness = 255;
            Exploded = false;
            BirthTime = millis();
            Mass = 5;
        }

        void Move()
        {
            if (Exploded == false){
                CurrentTime = millis();
                Location = Location + 1;
                if (Location >= Height)
                {
                    Exploded = true;
                }

            //Equations
            Location += .1 * Velocity;

            //Saturate Color
            if (Saturation < 256){
              Saturation = Saturation + 20;
              }
          }
          if (Exploded == true){
            //create fancy shrapnels here and pass hue & initial Velocity
            for (int i = 0; i < 5; i++){
              for (int j = -15; j <= 15; j +=5){
               initialVelocity = Velocity + i;
               shrapnel[i].Location = Location;
               shrapnel[i].Velocity = initialVelocity;
               shrapnel[i].Hue = Hue;
               }
             }
            //check if fancy shrapnels are alive
            for (int i = 0; i < 5; i++){
            shrapnel[i].Move();

            if (shrapnel[0].Burnout == true){
              //reload everything to 0
                  }
                }
            }
        }

        void Reset()
        {
            Location = 0;
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
          display->strips[display->numStrips/2][(int)Location].setHSV(Hue, Saturation, Brightness);
          for (int i = 0; i < 5; i++){
            shrapnel[i].draw(display);
          }
        }
};
