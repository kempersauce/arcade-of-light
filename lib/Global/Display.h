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
        }
};
