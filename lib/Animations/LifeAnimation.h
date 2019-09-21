#pragma once

#include <FastLED.h>
#include <Animation.h>
#include <Display.h>

class LifeAnimation : public Animation
{
    private:
        int width;
        int height;

        // We need 2 frames to write the changes each round
        int** frame1;//[NUM_STRIPS][NUM_LEDS];
        int** frame2;

        // Keep pointers to the frames so we can easily swap them each round instead of copying
        int ***lastRound = &frame1;
        int ***nextRound = &frame2;

        static const int ageColorMax = 3;
        CRGB* ageColors[ageColorMax + 1] = {
            new CRGB(0, 0, 0), // black
            new CRGB(0, 255, 0), // green
            new CRGB(0, 255, 255), // cyan
            new CRGB(0, 0, 255), // blue
        };

    public:
        LifeAnimation(int wdth, int heigt)
        {
            width = wdth;
            height = heigt;

            frame1 = new int*[width];
            frame2 = new int*[width];
            for (int i = 0; i < width; i++)
            {
                frame1[i] = new int[height];
                frame2[i] = new int[height];
            }

            lastRound = &frame1;
            nextRound = &frame2;
        }

        void setCellState(int x, int y, bool state)
        {
            if (x >= 0 && x < width
                && y >= 0 && y < height)
            {
                (*nextRound)[x][y] = state ? 1 : 0;
            }
        }

        void GoOneRound()
        {
            // swap last round with next round
            int ***placeholder = lastRound;
            lastRound = nextRound;
            nextRound = placeholder;

            // Calculate the next round based on the last one
            for (int strip = 0; strip < width; strip++)
            {
                for (int led = 0; led < height; led++)
                {
                    int neighborsAlive = 0;
                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            // don't count *this* cell
                            if (i == 0 && j == 0)
                            {
                                continue;
                            }

                            // calculate neighbor cell indices
                            int neighborStrip = (strip + i + width) % width;
                            int neighborLED = (led + j + height) % height;

                            // dont count out-of-bounds cells
                            if (neighborStrip < 0 || neighborStrip >= width
                                || neighborLED < 0 || neighborLED >= height)
                            {
                                continue;
                            }

                            // count up the 'alive' neighbors in the last round
                            if ((*lastRound)[neighborStrip][neighborLED])
                            {
                                neighborsAlive++;
                            }
                        }
                    }

                    bool isAlive;

                    if (neighborsAlive < 2)
                    {
                        isAlive = false;
                    }
                    else if (neighborsAlive > 3)
                    {
                        isAlive = false;
                    }
                    else if (neighborsAlive == 3)
                    {
                        isAlive = true;
                    }
                    else
                    {
                        isAlive = (*lastRound)[strip][led];
                    }

                    if (isAlive)
                    {
                        (*nextRound)[strip][led]++;
                    }
                    else
                    {
                        (*nextRound)[strip][led] = 0;
                    }
                }
            }
        }

        void draw(Display* display)
        {
            for (int ledIndex = 0; ledIndex < height; ledIndex++)
            {
                for (int stripIndex = 0; stripIndex < width; stripIndex++)
                {
                    int age = (*nextRound)[stripIndex][ledIndex];

                    // Dont let it step past the array bounds
                    if (age > ageColorMax)
                    {
                        age = ageColorMax;
                    }

                    display->strips[stripIndex][ledIndex] = *ageColors[age];
                }
            }
        }

        void randomize()
        {
            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    bool alive = random8() > 127;
                    setCellState(i, j, alive);
                }
            }
        }
};
