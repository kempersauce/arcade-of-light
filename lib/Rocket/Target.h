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
        Target(int loc, int height, CRGB* clr)
            : Animation()
        {
            Loc = loc;
            Height = height;
            Step = Height/6;
            color = clr;
            Time = 0;
            isInTarget = false;
        }

        void draw(Display* display)
        {
            int bottom = Loc;
            int top = bottom + Height;

            // Target bookends
            display->strips[0][bottom] = *color;
            display->strips[0][top] = *color;

            if (isInTarget)
            {
                long timeHeld = millis() - Time;
                int stage = (timeHeld + 500) / 1000;

                // Bottom fill
                int bottomFillStart = bottom + 1;
                int bottomFillEnd = bottomFillStart + Step * stage;

                for (int i = bottomFillStart; i < bottomFillEnd; i++)
                {
                    display->strips[0][i] = *color;
                }

                // Top fill
                int topFillEnd = top - 1;
                int topFillStart = topFillEnd - Step * stage;
                for (int i = topFillStart; i > topFillEnd; i++)
                {
                    display->strips[0][i] = *color;
                }
            }
        }
};
