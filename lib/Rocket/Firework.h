#include <Animation.h>

class Firework : Animation
{
    public:
        //location values
        int Loc;
        int Height; //pixel height where the firework explodes
        int Speed; //pixels per second

        //colors (RGB)
        int Red;
        int Green;
        int Blue;
        int loopCounter;

        // float Location;
        bool Exploded;
        bool burstFin;
        long Time;
        long oldTime;
        int burstSize;
        int explodeFrame;
        int slowDown;

        /**
         * Firework Constructor
         * @param loc - location on LED strip
         * @param red - red value (0-255)
         * @param green - green value (0-255)
         * @param blue - blue value (0-255)
         * */
        Firework()
            : Animation()
        {
            explodeFrame = -1;
            Loc = 0;
            Speed = random8(1,5);
            Height = random8(0,100)+150;
            Red = 255;
            Green = 0;
            Blue = 255;
            Exploded = false;
            burstFin = false;
            loopCounter = 0;
            slowDown = 2;
        }

        void Move()
        {
            if (Exploded == false)
            {
                oldTime = Time;
                Time = millis();
                Loc = Loc + 1;
                if (Loc >= Height)
                {
                    Exploded = true;
                }
            }
            //if (Exploded = true){
            //    loopCounter = loopCounter + 1;
            //}
            //Loc = (int)Location;
        }

        void Reset()
        {
            Loc = 0;
            //Location = 0;
            Speed = random8(1,5)+10;
            Height = random8(0,250)+50;
            Red = random(0,100);
            Green = random(0,100);
            Blue = random(0,100);
            Exploded = false;
            burstFin = false;
            loopCounter = 0;
        }

        void draw(Display* display)
        {

        }
};


 /*     int upDot = target.Loc + .5 * target.Height;
        int downDot = target.Loc + .5 * target.Height;
        int upFin = 0;
        int downFin = 0;
        // two way color fill across entire strip
        while (upFin + downFin != 2)
            {
                int redColor = random(0,255);
                int greenColor = random(0,255);
                int blueColor = random(0,255);
                if (upFin == 0){
                    leds[upDot].setRGB( greenColor, redColor, blueColor);
                    FastLED.show();
                    upDot = upDot + 1;
                    if (upDot > NUM_LEDS){
                        upFin = 1;
                    }
                }
                if (downFin == 0){
                    leds[downDot].setRGB( greenColor, redColor, blueColor);
                    FastLED.show();
                    downDot = downDot - 1;
                    if (downDot < 0){
                        downFin = 1;
                    }
                }
                //delay(animationDelay);
            } */
