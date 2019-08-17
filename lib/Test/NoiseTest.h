#include <Arduino.h>
#include <FastLED.h>
#include <Display.h>
#include <H2HDisplay.h>
#include <Game.h>
#include <Noise.h>

#define BRIGHTNESS 30
#define delayVal 0

class NoiseGame : Game
{
    public:
        NoiseGame(Display* gameDisplay)
            : Game(gameDisplay)
        {
        }

        void setup()
        {
            background = (Animation*)new Noise(display->numStrips, display->lengthStrips);
            FastLED.setBrightness(BRIGHTNESS);
        }

        void loop()
        {
            background->draw(display);
            FastLED.delay(delayVal);
            FastLED.show();
        }
};
