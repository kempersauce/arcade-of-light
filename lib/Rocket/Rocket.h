//Rocket Class
//Class that sets a dot in a specific locatio on the LED strip

#pragma once

#include <Animation.h>
#include <RocketBoost.h>
#include <PhysicsInfo.h>

class Rocket : Animation
{
public:
    PhysicsInfo physics;

    // Rocket constants
    //int Mass = 2;
    int Height = 2;
    //int Gravity; // this gets set according to the level

    //colors (RGB)
    CRGB* color;

    // Rocket State
    //float Thrust;
    //float ThrustMax = 200;
    //float Acceleration;
    //float Velocity;
    //float ExploadVelocity = 50;
    //float Location;
    //int LocationMax;
    //long Time;
    //bool Exploded;

    RocketBoost boost;

    /**
     * Rocket Constructor
     * @param loc - location on LED strip
     * @param clr - Color of the rocket ship
     */
    Rocket(int lengthStrips, CRGB* clr)
        : Animation(),
        physics(lengthStrips),
        boost(5)
    {
        physics.BounceFactor = -0.7;
        physics.ExplodeVelocity = 50;
        color = clr;
        Reset();
    }

    void Reset()
    {
        physics.Reset();
    }

    void SetGravity(int gravity)
    {
       physics.Gravity = gravity;
    }

    void SetBoost(int thrustLevel)
    {
        physics.Thrust = thrustLevel;
    }

    void Move(bool respectEdges = true)
    {
        physics.Move(respectEdges);

        // Update boost location
        boost.loc = physics.Location;
        boost.boostFactor = physics.Thrust / physics.ThrustMax;
    }

    void draw(Display* display)
    {
        // Draw the rocket boost
        boost.draw(display);

        // Draw the rocket ship
        int middleStrip = display->numStrips / 2;
        for (int i = max((int)physics.Location, 0); i < min((int)physics.Location + Height, display->lengthStrips); i++)
        {
            display->strips[middleStrip][i] = *color;
        }
    }
};
