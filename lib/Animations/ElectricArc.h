
#pragma once

#include <Display.h>

class ElectricArc : Animation
{
	vector<int> arc;
	CRGB color = CRGB::Purple;

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
				if (r <= UINT16_MAX * 2 / 5)
				{
					y += magnitude;
				}
				else if (r <= UINT16_MAX * 4 / 5)
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
			int arcHeight = arc[i];
			if (arcHeight >= 0 && arcHeight < display->lengthStrips)
			{
				display->strips[i][arcHeight] = CRGB::Purple;
			}

			arcHeight++;
			if (arcHeight > 0 && arcHeight < display->lengthStrips)
			{
				display->strips[i][arcHeight] = CRGB::Purple;
			}
		}
	}
};
