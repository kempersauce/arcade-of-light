/*
Display Class
holds the strips
*/

#pragma once

#include <Constants.h>

class Display
{
public:
    const int numStrips;
    const int lengthStrips;
    CRGB** strips;

    Display(const int numberOfStrips, const int lengthOfStrips)
        : numStrips(numberOfStrips), lengthStrips(lengthOfStrips)
    {
        strips = new CRGB*[numStrips];

        for (int i = 0; i < numStrips; i++)
		{
            strips[i] = new CRGB[lengthStrips];
        }
    }

    void blendPixel(int x, int y, CRGB* blendColor, float blendFactor)
    {
		if (y < lengthStrips)
		{
	        // get weighted blend values values
	        int red = strips[x][y].red * (1 - blendFactor) + blendColor->red * (blendFactor);
	        int green = strips[x][y].green * (1 - blendFactor) + blendColor->green * (blendFactor);
	        int blue = strips[x][y].blue * (1 - blendFactor) + blendColor->blue * (blendFactor);

	        // set the new values onto the pixel
	        strips[x][y].setRGB(red, green, blue);
		}
    }

	void ditherPixel(int stripIndex, float y, CRGB* color, float blendFactor = 1)
	{
		int yInt = y;
		float dither = y - yInt;
		blendPixel(stripIndex, yInt, color, (1 - dither) * blendFactor);
		blendPixel(stripIndex, yInt + 1, color, dither * blendFactor);
	}
};
