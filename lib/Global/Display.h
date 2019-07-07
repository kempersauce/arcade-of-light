/*
Display Class
holds the strips
*/
class Display {
    public:
        const int numStrips;
        const int lengthStrips;
        CRGB strips[][];

        Display(int numberOfStrips, int lengthOfStrips)
            : numStrips(numberOfStrips), lengthStrips(lengthOfStrips)
        {
            strips = new CRGB[numStrips][lengthStrips];

            //Relies on pin setup being sequential
            for (int i = 0; i < numStrips; i++) {
                FastLED.addLeds<WS2812B, (LED_PIN_0 + i), RGB>(strips[i], lengthStrips);
            }
        }
};
