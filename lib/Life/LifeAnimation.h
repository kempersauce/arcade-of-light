#pragma once

#include <FastLED.h>
#include <Animation.h>
#include <Display.h>
#include <vector>

using namespace std;

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

    public:
		float randomizeDensity = .2;

        vector<CRGB> ageColors {
            CRGB(0, 0, 0), // black
            CRGB(0, 255, 0), // green
            CRGB(0, 255, 255), // cyan
            CRGB(0, 0, 255), // blue
			CRGB(255, 0, 255), // magenta
			CRGB(255, 0, 0), // red
			CRGB(255, 255, 0), // yellow
        };

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

			randomize(); // init the nextRound just to be safe
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

                            // count up the 'alive' neighbors in the last round
                            if ((*lastRound)[neighborStrip][neighborLED] > 0)
                            {
                                neighborsAlive++;
                            }
                        }
                    }

                    int age = (*lastRound)[strip][led]; // 0 means dead
                    if (neighborsAlive < 2)
                    {
                        age = 0; // dead
                    }
                    else if (neighborsAlive > 3)
                    {
                        age = 0; // dead;
                    }
                    else if (neighborsAlive == 3)
                    {
                        age++; // bring the dead to life! and increment living cells
                    }
                    else
                    {
						// the old get older but nobody gets born here
                        if (age > 0)
						{
							age++;
						}
                    }

                    (*nextRound)[strip][led] = age;
                }
            }
        }

        void draw(Display* display)
        {
            for (int ledIndex = 0; ledIndex < display->lengthStrips; ledIndex++)
            {
                for (int stripIndex = 0; stripIndex < display->numStrips; stripIndex++)
                {
                    int age = (*nextRound)[stripIndex][ledIndex];

                    // Dont let it step past the array bounds
                    if (age >= ageColors.size())
                    {
                        age = ageColors.size() - 1;
                    }

                    display->strips[stripIndex][ledIndex] = ageColors[age];
                }
            }
        }

        void randomize()
        {
			uint16_t lifeThreshold = (float)UINT16_MAX * randomizeDensity;
            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    bool alive = random16() <= lifeThreshold;
					if (alive)
					{
						(*nextRound)[i][j] = 1;
					}
					else
					{
						(*nextRound)[i][j] = 0;
					}
                }
            }
        }
};
