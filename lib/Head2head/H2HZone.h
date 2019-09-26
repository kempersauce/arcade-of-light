#pragma once

#include <Display.h>

class H2HZone : public Animation
{
    public:
        CRGB color;
        int yMin;
        int yMax;
        int xLoc;

        H2HZone(CRGB startColor, int xLocation, int yMinimum, int yMaximum)
        {
            color = startColor;
            xLoc = xLocation;
            yMin = yMinimum;
            yMax = yMaximum;
        }

        bool checkZone(int y)
        {
            return y <= max(yMin, yMax) && y >= min(yMin, yMax);
        }

		// returns 0.0 to 1.0 based on how far into the zone the dot is
		float zoneDepth(int y)
		{
			float range = yMax - yMin; // negative when appropriate
			if (yMin < yMax) // right way up
			{
				return (float)(yMax - y) / range;
			}
			else // upside down
			{
				return (float)(y - yMin) / range;
			}
		}

        void draw(Display* display)
        {
            for (int y = yMin; y < yMax; y++)
            {
                display->strips[xLoc][y] = color;
            }
        }
};
