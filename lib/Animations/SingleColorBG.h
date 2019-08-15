#pragma once

#include <Display.h>
#include <Animation.h>

// Single color background
class SingleColorBG : Animation {
    public:
        //colors (RGB)
        int red;
        int green;
        int blue;

        SingleColorBG(int redColor, int greenColor, int blueColor) : Animation()
        {
            red = redColor;
            green = greenColor;
            blue = blueColor;
        }

        void setColor(int redColor, int greenColor, int blueColor)
        {
            red = redColor;
            green = greenColor;
            blue = blueColor;
        }

        void draw(Display* display)
        {
            for (int i = 0; i < display->lengthStrips; i++)
            {
                for (int j = 0; j < display->numStrips; j++)
                {
                    display->strips[j][i].setRGB(red, green, blue);
                }
            }
        }
};
