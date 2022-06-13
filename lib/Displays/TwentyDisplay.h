#pragma once

#include <Constants.h>
#include <Display.h>

/*
Display Class
holds the strips
*/
class TwentyDisplay : public Display {
    public:
        TwentyDisplay()
            : Display(20, 300)
        {
            FastLED.addLeds<WS2812B, LED_PIN_0, GRB>(strips[0], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_1, GRB>(strips[1], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_2, GRB>(strips[2], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_3, GRB>(strips[3], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_4, GRB>(strips[4], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_5, GRB>(strips[5], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_6, GRB>(strips[6], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_7, GRB>(strips[7], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_8, GRB>(strips[8], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_9, GRB>(strips[9], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_10, GRB>(strips[10], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_11, GRB>(strips[11], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_12, GRB>(strips[12], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_13, GRB>(strips[13], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_14, GRB>(strips[14], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_15, GRB>(strips[15], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_16, GRB>(strips[16], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_17, GRB>(strips[17], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_18, GRB>(strips[18], lengthStrips);
            FastLED.addLeds<WS2812B, LED_PIN_19, GRB>(strips[19], lengthStrips);
        }
};
