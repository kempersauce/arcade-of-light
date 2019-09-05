#pragma once

#include <Constants.h>
#include <Display.h>

/*
Display Class
holds the strips
*/
class FiveDisplay : public Display {
    public:
        FiveDisplay()
            : Display(5, 100)
        {
            FastLED.addLeds<WS2812B, LED_PIN_4, GRB>(strips[4], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_3, GRB>(strips[3], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_2, GRB>(strips[2], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_1, GRB>(strips[1], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_0, GRB>(strips[0], lengthStrips);
        }
};
