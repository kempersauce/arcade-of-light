#include <Animation.h>
#include <FancyShrapnel.h>

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
        bool Exploded;
  //      long BirthTime;
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
            Velocity = random8(1,5);  //pixels per second (I hope)
            Height = random8(0,100)+150;
            Hue = random(0,255);
            Saturation = 0;
            Brightness = 255;
            Exploded = false;
        }

        void Reset()
        {
          Location = 0;
          Velocity = random8(1,5);  //pixels per second (I hope)
          Height = random8(0,100)+150;
          Hue = random(0,255);
          Saturation = 0;
          Brightness = 255;
          Exploded = false;
        }

        void Move()
        {
            if (shrapnel[0].Burnout == true){Reset();}
            if (Exploded == true)
              {
                //create fancy shrapnels here and pass hue & initial Velocity
                for (int i = 0; i < 5; i++){
                  for (int j = -15; j <= 15; j +=5){
                   shrapnel[i].Location = Location;
                   shrapnel[i].Velocity = Velocity + j;
                   shrapnel[i].Hue = Hue;
                   shrapnel[i].BirthTime = millis();
                   }
                 }
                //check if fancy shrapnels are alive
                for (int i = 0; i < 5; i++){
                shrapnel[i].Move();
                if (shrapnel[0].Burnout == true){Reset();}
                  //reload everything to 0

                    }
                }
            if (Exploded == false)
            {
                CurrentTime = millis();
                Location++;
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
          display->strips[display->numStrips/2][(int)Location].setHSV(Hue, Saturation, Brightness);
          for (int i = 0; i < 5; i++){
            shrapnel[i].draw(display);
          }
        }
};
