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
    long frameRateMillis = 10;
    long flareFrameMillis = frameRateMillis/2;
    unsigned long lastLoopMillis;
    unsigned long lastFlareMillis;
    unsigned long newMillis;
    
    //flare
    int flareChance = 2;
    bool* hasFlare;
    int** flareLoc;

    NoiseGenerator* noiseGenerator;

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

        //randomly set first height
        int heightMod= random8(height+1);
        int newHeight = origin + heightMod;
        currentHeight[0] = newHeight;


        //noiseGenerator = new NoiseGenerator(width, height);
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

    void heightCheck(int index)
    {
        if(currentHeight[index]<= origin)
            {
                currentHeight[index] = origin;
            } 
            else if(currentHeight[index]>= maxHeight)
            {
                currentHeight[index] = origin + height;
            }
    }

    //Conjure the Flame
    void draw(Display *display)
    {
        //noiseGenerator->fillnoise8();
        newMillis = millis();
        
        // Serial.println("old: " + (String)lastLoopMillis);
        // Serial.println("new: " + (String)newMillis);
        // Serial.println("=============================");

        if((newMillis-lastLoopMillis)>=frameRateMillis)
        {
            //adjust 
            int heightAdjust= random16(3);
            if(random8()<=127)
            {
                heightAdjust *= -1;
            }
            currentHeight[0] += heightAdjust;
            heightCheck(0);
            
            Serial.println("FlameAni: 0 Height: " + (String)currentHeight[0]);
            for (int i = 1; i < display->numStrips; i++)
            {
                //Set flame height
                if(random8()<=127)
                {
                    heightAdjust *= -1;
                }
                currentHeight[i] = currentHeight[i-1] + heightAdjust;
                
                heightCheck(i);
                //flare logic
                if(!hasFlare[i]
                && currentHeight[i] <= (maxHeight - 2))
                {
                    hasFlare[i] = true;
                    flareLoc[i][0] = currentHeight[i];
                }
                heightCheck(i-1);
            }
            heightCheck(width-1);
            lastLoopMillis = millis();
        // }
        // //flare logic
        // if((newMillis-lastLoopMillis)>=lastFlareMillis)
        // {
            for (int i = 0; i < display->numStrips; i++)
            {
                //move flare up one
                flareLoc[i][0] += 1;
                //if at max, remove flag to draw next loop
                if(flareLoc[i][0] == maxHeight + 1)
                {
                    hasFlare[i] = false;
                }
                if(random8()<=127)
                {
                    hasFlare[i] = false;
                }
            }
            // lastFlareMillis = millis();
        }

        //draw flames
        drawFramesUp(display);
    }

    void drawFramesUp(Display *display)
    {
        for (int i = 0; i < display->numStrips; i++)
            {
                for (int j = origin; j <= currentHeight[i]; j++)
                {
                    //Serial.println("Flame Ani: in the loops");
                    //secondary color on last pixel
                    if(j == (currentHeight[i]) || j == (currentHeight[i]-1))
                    {
                        //display->strips[i][j] = CHSV(hueAccent, saturation, brightness);
                        //display->strips[i][j].setHSV(hueAccent, saturation, brightness + noiseGenerator->noise[i][flareLoc[i][0]]);
                        display->strips[i][j].setHSV(hueAccent, saturation, 255);
                    }
                    //main color on remaining pixel
                    else
                    {
                        //display->strips[i][j].setHSV(hueMain, saturation, brightness + noiseGenerator->noise[i][flareLoc[i][0]]);
                        display->strips[i][j].setHSV(hueMain, saturation, 255);
                        //display->strips[i][j] = CHSV(hueMain, saturation, brightness);
                    }
                }

                //Draw Flare
                if(hasFlare[i])
                {
                    CRGB color;
                    display->strips[i][flareLoc[i][0]].setHSV(hueAccent, saturation, 255);
                    //display->strips[i][flareLoc[i][0]].setHSV(hueAccent, saturation, brightness + noiseGenerator->noise[i][flareLoc[i][0]]);
                }
            }
    }
    void drawFramesDown(Display *display)
    {
        for (int i = 0; i < display->numStrips; i++)
            {
                for (int j = origin; j <= currentHeight[i]; j++)
                {
                    //Serial.println("Flame Ani: in the loops");
                    //secondary color on last pixel
                    if(j == (currentHeight[i]) || j == (currentHeight[i]-1))
                    {
                        //display->strips[i][j] = CHSV(hueAccent, saturation, brightness);
                        //display->strips[i][j].setHSV(hueAccent, saturation, brightness + noiseGenerator->noise[i][flareLoc[i][0]]);
                        display->strips[i][j].setHSV(hueAccent, saturation, 255);
                    }
                    //main color on remaining pixel
                    else
                    {
                        //display->strips[i][j].setHSV(hueMain, saturation, brightness + noiseGenerator->noise[i][flareLoc[i][0]]);
                        display->strips[i][j].setHSV(hueMain, saturation, 255);
                        //display->strips[i][j] = CHSV(hueMain, saturation, brightness);
                    }
                }

                //Draw Flare
                if(hasFlare[i])
                {
                    CRGB color;
                    display->strips[i][flareLoc[i][0]].setHSV(hueAccent, saturation, 255);
                    //display->strips[i][flareLoc[i][0]].setHSV(hueAccent, saturation, brightness + noiseGenerator->noise[i][flareLoc[i][0]]);
                }
            }
    }
};

