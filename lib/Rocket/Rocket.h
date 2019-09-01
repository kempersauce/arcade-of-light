//Rocket Class
//Class that sets a dot in a specific locatio on the LED strip

#pragma once

#include <Animation.h>

class Rocket : Animation
{
    public:
        // Rocket constants
        int Mass;
        int Height;
        int Gravity;
        int ThrustStrength;

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
            Gravity = 15;
            Mass = 2;
            Height = 2; //change this later to be adjustable
            color = clr;
            ThrustStrength = 200;
            Reset();
        }

        void Reset()
        {
          Location = 0;
          Thrust = 0;
          Velocity = 0;
          Acceleration = 0;
          Exploded = false;
          Time = millis();
        }

        void Boost()
        {
            Thrust = ThrustStrength;
        }

        void endBoost()
        {
            Thrust = 0;
        }

        void Move(int numLeds)
        {
            long oldTime = Time;
            //float oldAcceleration = Acceleration;

            Time = millis();

            //Equations
            //Acceleration [A] = (.5 * (Thrust + Previous Thrust))/mass-gravity
            Acceleration = Thrust/ Mass - Gravity;
            //will essentially be one of 3 values:
            //                  no thrust Acceleration = -GRAVITY
            //                  thrust initializing or ending = about 40% max thrust
            //                  full thrust = 100% thrust

            //Velocity [V] = Vp + delta T/1000 * Acceleration [A]
            //equation is for seconds millis() returns an unsigned long in milliseconds
            Velocity += ((Time - oldTime)/1000) * Acceleration;
            //needs to be min limited to 0 when position = 0
            //should probably have a terminal velocity since we only have 300px to work with

            //Position [Y] = Position Previous [Yp] + 0.5 * (Velocity [V] + Velocity Previous [Vp]) * delta T
            Location += Velocity * ((Time - oldTime)/1000);
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
                Velocity = 0;
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
        }
};
