#pragma once
#include <Animation.h>

class Flicker : public Animation
{
private:
    int hueMain = 0;
    int hueAccent = 0;
    int height = 5;
    int shiftSpeed = 1;

public:
    int saturation = 255;
    int brightness = 150;
    int origin = 12;

    //Initialize a Flame at y-location origin with a certain height, main color and accent color
        Flicker(int flameOrigin, int flameHeight, int mainHue, int accentHue) : Animation()
    {   
        hueMain = mainHue;
        hueAccent = accentHue;
        height = flameHeight;
        origin = flameOrigin;
    }
    //Sets the starting hue, probably not needed since the hue shifts constantly
    void setHues(int mainHue, int accentHue)
    {
        hueMain = mainHue;
        hueAccent = accentHue;
    }
    // Sets the saturation, 0=white 255=full color
    void setSaturation(int sat)
    {
        saturation = sat;
    }
    //Sets the Brightness, 0=off 255=max
    void setBrightness(int bright)
    {
        brightness = bright;
    }

    //Sets the flame shift rate or how much 
    void setSpeed(int speed)
    {
        shiftSpeed = speed;
    }


    //Conjure the Flame
    void draw(Display *display)
    {

        for (int i = 0; i < display->numStrips; i++)
        {
            //determine random height 
            int newHeight= random8(height);
            for (int j = origin; j <= newHeight; j++)
            {
                Serial.println("in the loops");
                //secondary color on last pixel
                if(j == (newHeight))
                {
                    display->strips[i][j] = CHSV(hueAccent, saturation, brightness);
                }
                //main color on remaining pixel
                else
                {
                    display->strips[i][j] = CHSV(hueMain, saturation, brightness);
                    if(newHeight%2 ==0)
                    {
                        display->strips[i][j+2] = CHSV(hueAccent, saturation, brightness);
                    }
                }
                
            }
        }
    }
};
