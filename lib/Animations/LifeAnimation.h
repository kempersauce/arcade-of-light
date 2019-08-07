#include <FastLED.h>
#include <Animation.h>
#include <Display.h>

class LifeAnimation : public Animation
{
    private:
        int width;
        int height;

        // We need 2 frames to write the changes each round
        bool** frame1;//[NUM_STRIPS][NUM_LEDS];
        bool** frame2;

        // Keep pointers to the frames so we can easily swap them each round instead of copying
        bool ***lastRound = &frame1;
        bool ***nextRound = &frame2;

    public:
        LifeAnimation(int wdth, int heigt)
        {
            width = wdth;
            height = heigt;

            frame1 = new bool*[width];
            frame2 = new bool*[width];
            for (int i = 0; i < width; i++)
            {
                frame1[i] = new bool[height];
                frame2[i] = new bool[height];
            }

            lastRound = &frame1;
            nextRound = &frame2;
        }

        void GoOneRound()
        {
            // swap last round with next round
            bool ***placeholder = lastRound;
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

                    (*nextRound)[strip][led] = isAlive;
                }
            }
        }

    public:
        void draw(Display* display)
        {
            for (int ledIndex = 0; ledIndex < height; ledIndex++)
            {
                for (int stripIndex = 0; stripIndex < width; stripIndex++)
                {
                    if ((*nextRound)[stripIndex][ledIndex])
                    {
                        display->strips[stripIndex][ledIndex] = CRGB::Amethyst;
                    }
                    else
                    {
                        display->strips[stripIndex][ledIndex] = CRGB::Black;
                    }
                }
            }
        }
};
