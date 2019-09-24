//Rocket Class
//Class that sets a dot in a specific locatio on the LED strip

#pragma once

#include <Animation.h>
#include <RocketBoost.h>

class Rocket : Animation
{
    public:
        // Rocket constants
        int Mass = 2;
        int Height = 2;
        int Gravity; // this gets set according to the level

        //colors (RGB)
        CRGB* color;

        // Rocket State
        float Thrust;
        float ThrustMax = 200;
        float Acceleration;
        float Velocity;
        float ExploadVelocity = 50;
        float Location;
        int LocationMax;
        float Time;
        bool Exploded;

        RocketBoost boost;

        /**
         * Rocket Constructor
         * @param loc - location on LED strip
         * @param clr - Color of the rocket ship
         */
        Rocket(int lengthStrips, CRGB* clr)
            : Animation(),
            boost(5)
        {
            LocationMax = lengthStrips;
            Gravity = 15;
            color = clr;
            Reset();
        }

        void Reset()
        {
            Location = 0;
            Velocity = 0;
            Acceleration = 0;
            Exploded = false;
            SetBoost(0);
            Time = millis();
        }

        void SetGravity(int gravity)
        {
           Gravity = gravity;
        }

        void SetBoost(int thrustLevel)
        {
            if (thrustLevel > ThrustMax)
            {
                Thrust = ThrustMax;
                boost.boostFactor = 1;
            }
            else
            {
                Thrust = thrustLevel;
                boost.boostFactor = Thrust / ThrustMax;
            }
        }

        void Move(bool respectEdges = true)
        {
            float timeDiff = (float)((millis() - Time) / 1000);

            Time = millis();

            //Equations
            //Acceleration [A] = (.5 * (Thrust + Previous Thrust))/mass-gravity
            Acceleration = (float)Thrust / (float)Mass - Gravity;
            //will essentially be one of 3 values:
            //                  no thrust Acceleration = -GRAVITY
            //                  thrust initializing or ending = about 40% max thrust
            //                  full thrust = 100% thrust

            //Velocity [V] = Vp + delta T/1000 * Acceleration [A]
            //equation is for seconds millis() returns an unsigned long in milliseconds
            Velocity += Acceleration * timeDiff;
            //needs to be min limited to 0 when position = 0
            //should probably have a terminal velocity since we only have 300px to work with

            //Position [Y] = Position Previous [Yp] + 0.5 * (Velocity [V] + Velocity Previous [Vp]) * delta T
            Location += Velocity * timeDiff;
            //needs to be min limited to 0

            if (respectEdges)
            {
                //rocket has slammed into ceiling or floor
                bool hasHitEdge = false;
                if (Location >= LocationMax)
                {
                    Location = LocationMax - 1;
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
                    if (abs(Velocity) >= ExploadVelocity)
                    {
                        Exploded = true;
                    }

                    // and bounced off ceiling/floor
                    else
                    {
                        Velocity = -0.7 * Velocity;
                    }
                }
            }

            // Update boost location
            boost.loc = Location;
        }

        void draw(Display* display)
        {
            // Draw the rocket boost
            boost.draw(display);

            // Draw the rocket ship
            int middleStrip = display->numStrips / 2;
            for (int i = max((int)Location, 0); i < min((int)Location + Height, display->lengthStrips); i++)
            {
                display->strips[middleStrip][i] = *color;
            }
        }
};
