#include <Constants.h>

/*
Display Class
holds the strips
*/
class Display {
    public:
        const int numStrips;
        const int lengthStrips;
        CRGB** strips;

        Display(const int numberOfStrips, const int lengthOfStrips)
            : numStrips(numberOfStrips), lengthStrips(lengthOfStrips)
        {
            strips = new CRGB*[numStrips];

            //Relies on pin setup being sequential
            for (int i = 0; i < numStrips; i++) {
                strips[i] = new CRGB[lengthStrips];
            }

            // setup as many strips as we need - addLeds forces us to do it this way for the compiler
            switch (numStrips)
            {
                default:  
                case 8:
                    FastLED.addLeds<WS2812B, LED_PIN_7, RGB>(strips[7], lengthStrips);

                case 7:
                    FastLED.addLeds<WS2812B, LED_PIN_6, RGB>(strips[6], lengthStrips);

                case 6:
                    FastLED.addLeds<WS2812B, LED_PIN_5, RGB>(strips[5], lengthStrips);

                case 5:
                    FastLED.addLeds<WS2812B, LED_PIN_4, RGB>(strips[4], lengthStrips);

                case 4:
                    FastLED.addLeds<WS2812B, LED_PIN_3, RGB>(strips[3], lengthStrips);

                case 3:
                    FastLED.addLeds<WS2812B, LED_PIN_2, RGB>(strips[2], lengthStrips);

                case 2:
                    FastLED.addLeds<WS2812B, LED_PIN_1, RGB>(strips[1], lengthStrips);

                case 1:
                    FastLED.addLeds<WS2812B, LED_PIN_0, RGB>(strips[0], lengthStrips);
                    break;
            }
        }
};
