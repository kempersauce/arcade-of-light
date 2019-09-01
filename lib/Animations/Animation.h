/*
Animation class
Make the pretty lights
Make the lights pretty
*/

#pragma once

#include <Display.h>

class Animation
{
    public:
        virtual void draw(Display* display);

        void blendPixel(CRGB* pix, CRGB* blendColor, float blendFactor)
        {
            // get weighted blend values values
            int red = pix->red * (1 - blendFactor) + blendColor->red * (blendFactor);
            int green = pix->green * (1 - blendFactor) + blendColor->green * (blendFactor);
            int blue = pix->blue * (1 - blendFactor) + blendColor->blue * (blendFactor);

            // set the new values onto the pixel
            pix->setRGB(red, green, blue);
        }
};
