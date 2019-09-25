
#pragma once

class PhysicsInfo
{
public:
    float Acceleration;
    float Velocity;
    float Location;
    int LocationMax;

    long Time;

    int Mass = 1; // default to 1 so Thrust = Acceleration
    int Gravity = 0; // default to 0 for no gravity
    float Thrust;
    float ThrustMax = 200; // ???

    bool HasHitEdge;
    float BounceFactor = 1.0; // default to 1 for no bounce

    bool HasExploded;
    int ExplodeVelocity = UINT16_MAX; // default to this to hopefully never explode

    PhysicsInfo(int maxLoc)
    {
        LocationMax = maxLoc;
        Reset();
    }

    void Reset()
    {
        Acceleration = 0;
        Velocity = 0;
        Location = 0;
        Thrust = 0;
        HasHitEdge = false;
        HasExploded = false;
        Time = millis();
    }

    void Move(bool respectEdges = true)
    {
        if (Thrust > ThrustMax)
        {
            Thrust = ThrustMax;
        }

        float timeDiff = (float)(millis() - Time) / 1000;

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

        HasHitEdge = (Location < 0 || Location >= LocationMax);

        if (respectEdges)
        {
            //rocket has slammed into ceiling or floor
            if (Location >= LocationMax)
            {
                Location = LocationMax - 1;
            }
            else if (Location <= 0)
            {
                Location = 0;
            }

            if (HasHitEdge)
            {
                Acceleration = 0;

                // and exploded
                if (abs(Velocity) >= ExplodeVelocity)
                {
                    HasExploded = true;
                }

                // and bounced off ceiling/floor
                else
                {
                    Velocity *= BounceFactor;
                }
            }
        }
    }
};
