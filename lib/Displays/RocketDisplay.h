#include <Constants.h>

/*
Display Class
holds the strips
*/
class RocketDisplay : public Display
{
    public:
        RocketDisplay()
            : Display(1, 600)
        {
            FastLED.addLeds<WS2812B, 20, GRB>(strips[0], lengthStrips);
        }
};
