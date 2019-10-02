
#pragma once

class PhysicsInfo
{
    // Track physics based on time not frames
    long Time;

    // This is calculated and overwritten immediately - instead set thrust
    float Acceleration;

public:
    // Dynamic values
	// TODO make this handle Y values too ?!?! at least velocity and location are needed for firework.explosion
    float Thrust;
    float Velocity;
    float Location;
	float Friction = 0;

	float xVelocity = 0;
	float xLocation = 0;
	float xFriction = 0;

    // Edge detection
    bool HasHitEdge; // updated every round to determine if the edge was hit this round
    bool HasExploded; // set to true when exploded, only reset on Reset()

    // Configurable values - these default to values that make them not used unless set
    int LocationMax = UINT16_MAX; // default to this to have no ceiling ... 0 is still hardcoded on the bottom
    float ThrustMax = 200; // ???
    int Mass = 1; // default to 1 so Thrust = Acceleration
    int Gravity = 0; // default to 0 for no gravity
    float BounceFactor = 1.0; // default to 1 for no bounce
    int ExplodeVelocity = 0; // default to 0 to explode on contact

    PhysicsInfo()
    {
        Reset();
    }

	void RandomizeVelocityVector(float maxMagnitude)
	{
		float x, y;
		do {
			x = ((float)random16() / (float)UINT16_MAX) * 2 - 1; // -1.0 to 1.0
			y = ((float)random16() / (float)UINT16_MAX) * 2 - 1; // -1.0 to 1.0
		} while(x * x + y * y > 1); // Repeat until we're within the unit circle

		Velocity = y * maxMagnitude;
		xVelocity = x * maxMagnitude;
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
		Velocity -= Velocity * Friction * timeDiff;
		xVelocity -= xVelocity * xFriction * timeDiff;

        //needs to be min limited to 0 when position = 0
        //should probably have a terminal velocity since we only have 300px to work with

        //Position [Y] = Position Previous [Yp] + 0.5 * (Velocity [V] + Velocity Previous [Vp]) * delta T
        Location += Velocity * timeDiff;
		xLocation += xVelocity * timeDiff;
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
