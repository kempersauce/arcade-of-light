#pragma once
#include <Animation.h>
#include <NoiseGenerator.h>

class Flicker : public Animation
{
private:
    int hueMain = 0;
    int hueAccent = 0;
    int height;
    int* currentHeight; //<-- stores height data
    int maxHeight = origin + height;
    int width;
    int shiftSpeed = 1;

    //frame rate
    long frameRateMillis = 50;
    long flareFrameMillis = frameRateMillis/2;
    unsigned long lastLoopMillis;
    unsigned long newMillis;
    
    //flare
    int flareChance = 2;
    bool* hasFlare;
    int** flareLoc;

    NoiseGenerator* noise;

public:
    int saturation = 255;
    int brightness = 150;
    int origin = 12;

    //Initialize a Flame at y-location origin with a certain height, main color and accent color
        Flicker(int flameOrigin, int flameHeight, int flameWidth, int mainHue, int accentHue) : Animation()
    {   
        hueMain = mainHue;
        hueAccent = accentHue;
        height = flameHeight;
        origin = flameOrigin;
        width = flameWidth;
        currentHeight = new int[width];

        hasFlare = new bool[width];
        flareLoc = new int*[width];

        for(int i=0; i<width;i++)
        {
            currentHeight[i] = height/2;
            hasFlare[i] = false;
            flareLoc[i] = new int[0];
            flareLoc[i][0] = maxHeight -1;
            Serial.println("FlameAni: Height " + (String)i + ": " + (String)currentHeight[i]);
        }

        noise = new NoiseGenerator(width, height);
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
        newMillis = millis();
        Serial.println("old: " + (String)lastLoopMillis);
        Serial.println("new: " + (String)newMillis);
        Serial.println("=============================");

        if((newMillis-lastLoopMillis)>=frameRateMillis)
        {
            //determine random height 
            
            for (int i = 0; i < display->numStrips; i++)
            {
                //Set flame height
                int heightMod= random8(height+1);
                int newHeight = origin + heightMod;
                currentHeight[i] = newHeight;
                //flare logic
                if(!hasFlare[i] 
                && (random8(100) + 1) % flareChance == 0 
                && currentHeight[i] <= (maxHeight - 2))
                {
                    hasFlare[i] = true;
                    flareLoc[i][0] = currentHeight[i];
                }
            }
            lastLoopMillis = millis();
        }
        if((newMillis-lastLoopMillis)>=flareFrameMillis)
        {
            for (int i = 0; i < display->numStrips; i++)
            {
                //move flare up one
                flareLoc[i][0] += 1;
                //if at max, remove flag to draw next loop
                if(flareLoc[i][0] == maxHeight + 1)
                {
                    hasFlare[i] = false;
                }
            }
        }

        //draw flames
        for (int i = 0; i < display->numStrips; i++)
        {

            for (int j = origin; j <= currentHeight[i]; j++)
            {
                Serial.println("Flame Ani: in the loops");
                //secondary color on last pixel
                if(j == (currentHeight[i]))
                {
                    //display->strips[i][j] = CHSV(hueAccent, saturation, brightness);
                    //dithering
                    CRGB color;
                    color.setHSV(hueAccent, saturation, 255);
                    display->ditherPixel(i,j,&color);
                }
                //main color on remaining pixel
                else
                {
                    //dithering
                    CRGB color;
                    color.setHSV(hueMain, saturation, 255);
                    display->ditherPixel(i,j,&color);
                    //display->strips[i][j] = CHSV(hueMain, saturation, brightness);
                }
            }
            //Draw Flare
            if(hasFlare[i])
            {
                
                CRGB color;
                color.setHSV(hueAccent, saturation, 255);
                display->ditherPixel(i,flareLoc[i][0],&color);
            }
        }
    }
};
