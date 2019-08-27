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
            return y <= yMax && y >= yMin;
        }

        void draw(Display* display)
        {
            for (int y = yMin; y < yMax; y++)
            {
                display->strips[xLoc][y] = color;
            }
        }
};
