#pragma once

#include <Animation.h>

class Explosion : Animation
{
	long birthTime;
	static const long burnoutTimeMillis = 1000 * 3; // 5 seconds

public:
	static const int shrapnelCount = 50;
    PhysicsInfo shrapnel[shrapnelCount];

    //colors (HSV)
    int Hue;

	int stripIndex;

    Explosion()
        : Animation()
    {
        Hue = random(0, 255);

		// Try putting a little bit of gravity on here
		for (int i = 0; i < shrapnelCount; i++)
		{
			shrapnel[i].Gravity = 6;
		}
    }

    void ExplodeAt(int location)
    {
        birthTime = millis();

		for (int i = 0; i < shrapnelCount; i++)
		{
			shrapnel[i].Reset();
			shrapnel[i].Location = location;
			shrapnel[i].xLocation = stripIndex;
			shrapnel[i].RandomizeVelocityVector(50);
		}
    }

    void Move()
    {
		for (int i = 0; i < shrapnelCount; i++)
		{
			shrapnel[i].Move();
			shrapnel[i].Velocity *= .9;
			shrapnel[i].xVelocity *= .5;
		}
    }

	bool IsBurnedOut()
	{
		return millis() - birthTime >= burnoutTimeMillis;
	}

    void draw(Display* display)
    {
		float timeDiff = (float)(millis() - birthTime) / 1000;

		if (timeDiff <= 3.5) // don't drawing after the explosion burns out
		{
			// Saturate Color for 2 seconds
			int Saturation = min(255 * timeDiff / 1, 255);

			// Then fade to Black for the next 1.5 seconds
			int Brightness = min(max(255 - (255 * (timeDiff - 1) / 1.5), 0), 255);

			int midStrip = display->numStrips / 2;
			for (int i = 0; i < shrapnelCount; i++)
			{
				int loc = (int)shrapnel[i].Location;
				int xLoc = (int)shrapnel[i].xLocation;
				if (loc >= 0 && loc < display->lengthStrips && xLoc >= 0 && xLoc < display->numStrips)
				{
					CRGB clr;
					clr.setHSV(Hue, Saturation, Brightness);
					float blend = (float)Brightness / (float)255;
					display->ditherPixel(xLoc, shrapnel[i].Location, &clr, blend);
				}
			}
		}
    }
};
