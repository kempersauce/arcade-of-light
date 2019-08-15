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

        bool checkZone(int x, int y)
        {
            bool result = false;
            if(x == xLoc)
            {
                if(y<=yMax && y>=yMin)
                {
                    result = true;
                }
            }
            return result;
        }

        void draw(Display* display)
        {
            for(int y=yMin; y<yMax; y++)
            {
                display->strips[xLoc][y] = color;
            }
        }
};
