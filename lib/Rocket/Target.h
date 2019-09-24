/*Target Class
Class that sets a series of dots in a specific location on the LED strip
*/

#include <Animation.h>

class Target : Animation
{
    public:
        int Loc;
        int Height;
        int Step;
        CRGB* color;
        long Time;
        bool isInTarget;

        //Constructor
        Target(CRGB* clr)
            : Animation()
        {
            color = clr;
            Time = 0;
            isInTarget = false;
        }

        void setColor(CRGB* clr)
        {
            color = clr;
        }

        void randomize(int lengthStrips)
        {
            Loc = random(lengthStrips / 4, lengthStrips - 20);
            Height = random(5, 20);
            Step = Height / 6;
        }

        void setToGround()
        {
            Loc = 5;
            Height = 10;
            Step = Height / 6;
        }

        void draw(Display* display)
        {
            int bottom = Loc;
            int top = bottom + Height;

            // Draw the target accross all numStrips
            for (int j = 0; j < display->numStrips; j++)
            {
                // Target bookends
                if (bottom >= 0)
                    display->strips[j][bottom] = *color;

                if (top >= 0)
                    display->strips[j][top] = *color;

                if (isInTarget)
                {
                    long timeHeld = millis() - Time;
                    float stage = (timeHeld + 500) / 1000;

                    // Bottom fill
                    int bottomFillStart = bottom + 1;
                    int bottomFillEnd = bottomFillStart + Step * stage;

                    for (int i = max(bottomFillStart, 0); i < bottomFillEnd; i++)
                    {
                        display->strips[j][i] = *color;
                    }

                    // Top fill
                    int topFillEnd = top;
                    int topFillStart = topFillEnd - Step * stage;
                    for (int i = max(topFillStart, 0); i < topFillEnd; i++)
                    {
                        display->strips[j][i] = *color;
                    }
                }
            }
        }
};
