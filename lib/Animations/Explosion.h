#pragma once

#include <Animation.h>
#include <vector>

using namespace std;

class Explosion : Animation
{
public:
	long birthTimeMillis;

    vector<PhysicsInfo> shrapnel;

    //colors (HSV)
    int Hue;
	int SaturationFinal = 255;
	long saturationPhaseMillis = 1000;
	long brightnessPhaseMillis = 1500;

    Explosion(int shrapnelCount = 50)
        : Animation(),
		shrapnel(shrapnelCount)
    {
		birthTimeMillis = 0; // not born yet
        Hue = random(0, 255);
    }

	void SetGravity(int gravity)
	{
		for (int i = 0; i < shrapnel.size(); i++)
		{
			shrapnel[i].Gravity = gravity;
		}
	}

    void ExplodeAt(int stripIndex, int location)
    {
        birthTimeMillis = millis();


		for (int i = 0; i < shrapnel.size(); i++)
		{
			shrapnel[i].Reset();
			shrapnel[i].Location = location;
			shrapnel[i].xLocation = stripIndex;
			shrapnel[i].RandomizeVelocityVector(50);
		}
    }

    void Move()
    {
		if (IsBurnedOut() == false)
		{
			for (int i = 0; i < shrapnel.size(); i++)
			{
				shrapnel[i].Move();
				shrapnel[i].Velocity *= .9;
				shrapnel[i].xVelocity *= .5;
			}
		}
    }

	bool IsBurnedOut()
	{
		return TimeAliveMillis() >= saturationPhaseMillis + brightnessPhaseMillis;
	}

	long TimeAliveMillis()
	{
		return millis() - birthTimeMillis;
	}

    void draw(Display* display)
    {

		if (IsBurnedOut()) // don't drawing after the explosion burns out
		{
			return;
		}

		long timeAliveMillis = TimeAliveMillis();

		// Saturate Color while we're in the saturation phase
		int saturation;
		if (timeAliveMillis < saturationPhaseMillis)
		{
			saturation = SaturationFinal * (float)timeAliveMillis / (float)saturationPhaseMillis;
		}
		else
		{
			saturation = SaturationFinal;
		}

		timeAliveMillis -= saturationPhaseMillis;

		// Then fade to Black for the brightness phase
		int brightness;
		if (timeAliveMillis < 0)
		{
			brightness = 255;
		}
		else if (timeAliveMillis < brightnessPhaseMillis)
		{
			brightness = 255 * (1.0 - (float)timeAliveMillis / (float)brightnessPhaseMillis);
		}
		else
		{
			brightness = 0;
		}

		for (int i = 0; i < shrapnel.size(); i++)
		{
			int loc = (int)shrapnel[i].Location;
			int xLoc = (int)shrapnel[i].xLocation;
			if (loc >= 0 && loc < display->lengthStrips && xLoc >= 0 && xLoc < display->numStrips)
			{
				CRGB clr;
				clr.setHSV(Hue, saturation, brightness);
				float blend = (float)brightness / (float)255;
				display->ditherPixel(xLoc, shrapnel[i].Location, &clr, blend);
			}
		}
    }
};
