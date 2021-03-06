#include <Animation.h>

class Platform : Animation
{
    public:
        int Loc;
        int Width;
        int Hole;
        CHSV* color;

        //Constructor
        Target(int loc, int width, CRGB* clr)
            : Animation()
        {
            Loc = loc;
            Height = width;
            color = clr;
        }

        void draw(Display* display)
        {
            int bottom = Loc;
            int top = bottom + Height;

            // Draw the target accross all numStrips
            for (int j = 0; j < display->numStrips; j++)
            {
                // Target bookends
                display->strips[j][bottom] = *color;
                display->strips[j][top] = *color;

            }
        }

        void Move(){

        };

        Void Interact(){

        };

        Void Reset(){

        };
};
