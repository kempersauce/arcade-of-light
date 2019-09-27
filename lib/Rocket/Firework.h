#include <Animation.h>
#include <Explosion.h>

class Firework : Animation
{
	// Used to randomly select the strip and explosion height when resetting the firework
	int stripsHeight;
	int stripsWidth;

	int stripIndex;

public:
    // Physics for the fireworks "rocket"
    PhysicsInfo physics;

	// Fireworks explosion
    Explosion explosion;

    //color for the firework rocket
    int Hue;

    /**
     * Firework Constructor
     * @param stripLength - location on LED strip
     * */
    Firework(int stripLength, int numStrips)
        : Animation(),
        physics()
    {
        stripsHeight = stripLength;
		stripsWidth = numStrips;
        Reset();
    }

    void Reset()
    {
        physics.Reset();
        physics.LocationMax = random(stripsHeight / 3, stripsHeight - 20); // height the firework explodes
        physics.Velocity = random(35, 75); // how fast do we get there

		stripIndex = random(0, stripsWidth); // select which strip this should be on
		explosion.stripIndex = stripIndex;

        Hue = random(0, 255); //
    }

    void Move()
    {
		bool wasExploded = physics.HasExploded; // edge was set with LocationMax to denote the explode height

		// Shoot again
		if (wasExploded && explosion.IsBurnedOut())
		{
			Reset();
		}

        physics.Move();

		// Explode when we get to the designated height
        if (physics.HasExploded)
        {
			if (wasExploded == false)
			{
				explosion.Hue = random(0, 255);
				explosion.ExplodeAt(physics.Location);
			}

			explosion.Move();
        }
    }

    void draw(Display* display)
    {
        if (physics.HasExploded)
        {
			explosion.draw(display);
		}
		else
		{
			int Saturation = min(255 * (physics.Location / physics.LocationMax), 255);
            display->strips[stripIndex][(int)physics.Location].setHSV(Hue, Saturation, 255);
        }
    }
};
