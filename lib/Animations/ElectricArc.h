
#pragma once

#include <Display.h>

class ElectricArc : Animation
{
	vector<int> arc;
public:
	int yLocation;

    virtual void draw(Display* display)
	{
		arc.clear();

		do
		{
			int y = yLocation;
			arc.push_back(y);
			for (int x = 1; x < display->numStrips; x++)
			{
				if (random16() <= UINT16_MAX / 2)
				{
					y++;
				}
				else
				{
					y--;
				}
				arc.push_back(y);
			}
		} while (arc.front() != arc.back());

		for (int i = 0; i < arc.size(); i++)
		{
			display->strips[i][arc[i]] = CRGB::White;
		}
	}
};
