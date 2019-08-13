#include <Constants.h>

/*
Display Class
holds the strips
*/
class RocketDisplay : public Display
{
    public:
        RocketDisplay()
            : Display(1, 300)
        {
            FastLED.addLeds<WS2812B, LED_PIN_0, GRB>(strips[0], lengthStrips);
        }
};
