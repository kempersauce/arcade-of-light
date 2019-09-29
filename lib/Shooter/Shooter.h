# pragma once

#include <Animation.h>
#include <PhysicsInfo.h>

class Shooter : Animation
{
public:
	PhysicsInfo physics;

	Shooter()
		: Animation(),
		physics()
	{
	}

	void draw(Display* display)
	{
		for (int x = max(physics.xLocation - 1, 0); x < min(physics.xLocation + 2, display->numStrips); x++)
		{
			display->strips[x][(int)physics.Location] = CRGB::Magenta;
		}
	}
};
