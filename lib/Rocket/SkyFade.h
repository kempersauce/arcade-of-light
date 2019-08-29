/*
SkyFade class
Draws a blue color,
fading back to the original color a third of the way up
*/
#pragma once
#include <Animation.h>

class SkyFade : Animation
{
    private:
        void blendPixelBlue(CRGB* pix, float blueFactor)
        {
            // get initial values
            int red = pix->red;
            int green = pix->green;
            int blue = pix->blue;

            // fade to blue
            red -= red * blueFactor;
            green -= green * blueFactor;
            blue += (255 - blue) * blueFactor;

            // set the new values onto the pixel
            pix->setRGB(red, green, blue);
        }

    public:
        void draw(Display* display)
        {
            int heightMax = display->lengthStrips / 3; // only go a third of the way up
            for (int i = 0; i < display->numStrips; i++)
            {
                for (int j = 0; j < heightMax; j++)
                {
                    float blueFactor = ((float)(heightMax - j)) / ((float)heightMax);
                    blendPixelBlue(&display->strips[i][j], blueFactor);
                }
            }
        }
};
