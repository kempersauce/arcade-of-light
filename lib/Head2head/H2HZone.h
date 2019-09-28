#pragma once

#include <Display.h>

class H2HZone : public Animation
{
    public:
        CRGB color;
        int yMin;
        int yMax;
        int xLoc;

		bool upsideDown;

        H2HZone(CRGB startColor, int xLocation, int yMinimum, int yMaximum, bool isTop)
        {
            color = startColor;
            xLoc = xLocation;
            yMin = yMinimum;
            yMax = yMaximum;

			upsideDown = isTop;
        }

        bool checkZone(int y)
        {
            return y >= yMin && y <= yMax;
        }

		// returns 0.0 to 1.0 based on how far into the zone the dot is
		float zoneDepth(int y)
		{
			float range = yMax - yMin;

			// BOTTOM - SPECIFIC CALCULATION
			if (upsideDown)
			{
				return (float)(y - yMin) / range;
			}
			else
			{
				return (float)(yMax - y) / range;
			}
		}

        void draw(Display* display)
        {
            for (int y = yMin; y <= yMax; y++)
            {
                display->strips[xLoc][y] = color;
            }
        }
};
