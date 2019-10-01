
#pragma once

#include <Display.h>

class ElectricArc : Animation
{
	vector<int> arc;
public:
	int yLocation;
	float magnitude = 2.0;

    virtual void draw(Display* display)
	{
		do
		{
			arc.clear();
			int y = yLocation;
			arc.push_back(y);
			for (int x = 1; x < display->numStrips; x++)
			{
				int r = random16();
				if (r <= UINT16_MAX / 3)
				{
					y += magnitude;
				}
				else if (r <= UINT16_MAX * 2 / 3)
				{
					y -= magnitude;
				}
				else
				{
					//nothing
				}

				arc.push_back(y);
			}
		} while (arc.front() != arc.back());

		for (int i = 0; i < arc.size(); i++)
		{
			display->strips[i][arc[i]] = CRGB::White;
			display->strips[i][arc[i] + 1] = CRGB::White;
		}
	}
};
