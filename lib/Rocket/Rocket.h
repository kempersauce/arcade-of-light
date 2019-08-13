//Rocket Class
//Class that sets a dot in a specific locatio on the LED strip

#pragma once

#include <Animation.h>

#define MASS 2
#define GRAVITY 15
#define THRUST 200

class Rocket : Animation
{
    public:
        // Rocket constants
        int Mass;
        int Height;

        //colors (RGB)
        CRGB* color;

        // Rocket State
        float Location;
        float Thrust;
        float Velocity;
        float Acceleration;
        float Time;
        bool Exploded;

        /**
         * Rocket Constructor
         * @param loc - location on LED strip
         * @param clr - Color of the rocket ship
         */
        Rocket(int loc, CRGB* clr)
            : Animation(),
            Location((float)loc)
        {
            Mass = MASS;
            Height = 1; //change this later to be adjustable
            color = clr;
            Thrust = 0;
            Velocity = 0;
            Acceleration = 0;
            Exploded = false;
        }

        void Boost()
        {
            Thrust = THRUST;
        }

        void endBoost()
        {
            Thrust = 0;
        }

        void Move(int numLeds)
        {
            long oldTime = Time;
            float oldThrust = Thrust;
            float oldVelocity = Velocity;
            float oldLocation = Location;
            float oldAcceleration = Acceleration;

            Time = millis();

            //Equations
            //Acceleration [A] = (.5 * (Thrust + Previous Thrust))/mass-gravity
            Acceleration = ( .5 * (Thrust + oldThrust))/ Mass - GRAVITY;
            //will essentially be one of 3 values:
            //                  no thrust Acceleration = -GRAVITY
            //                  thrust initializing or ending = about 40% max thrust
            //                  full thrust = 100% thrust

            //Velocity [V] = Vp + delta T/1000 * Acceleration [A]
            //equation is for seconds millis() returns an unsigned long in milliseconds
            Velocity = oldVelocity + ((Time - oldTime)/1000) * Acceleration;
            //needs to be min limited to 0 when position = 0
            //should probably have a terminal velocity since we only have 300px to work with

            //Position [Y] = Position Previous [Yp] + 0.5 * (Velocity [V] + Velocity Previous [Vp]) * delta T
            Location = oldLocation + (.5 * (Velocity + oldVelocity)) * ((Time - oldTime)/1000);
            //needs to be min limited to 0

            //rocket has slammed into ceiling or floor
            bool hasHitEdge = false;
            if (Location > numLeds - 1)
            {
                Location = numLeds - 1;
                hasHitEdge = true;
            }
            else if (Location <= 0)
            {
                Location = 0;
                hasHitEdge = true;
            }

            if (hasHitEdge)
            {
                Acceleration = 0;

                // and exploded
                if (Velocity > 100)
                {
                    Exploded = true;
                    Velocity = 0;
                }

                // and bounced off ceiling
                else
                {
                    Velocity = -0.7 * Velocity;
                }
            }
        }

        void draw(Display* display)
        {
            // Draw the rocket ship
            int middleStrip = display->numStrips / 2;
            for (int i = (int)Location; i < (int)Location + Height; i++)
            {
                display->strips[middleStrip][i] = *color;
            }

            // draw the boost
            // TODO implement variable thrust?
            if (Thrust > 0)
            {
                int flame1 = (int)Location - 1;
                int flame2 = (int)Location - 2;
                int flame3 = (int)Location - 3;
                int flame4 = (int)Location - 4;
                display->strips[middleStrip][flame1].setRGB(255,255,0);
                display->strips[middleStrip][flame2].setRGB(191,255,0);
                display->strips[middleStrip][flame3].setRGB(128,255,0);
                display->strips[middleStrip][flame4].setRGB(0,100,0);
            }
        }
};
