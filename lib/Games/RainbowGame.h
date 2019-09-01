/*
Game class
Where the magic happens
*/

#pragma once

#include <HueRainbow.h>

class RainbowGame : Game
{
    public:
        HueRainbow* rainbow;

        RainbowGame(Display* gameDisplay)
            : Game(gameDisplay)
        {
            rainbow = new HueRainbow(2);
        }

        void setup()
        {
          ((HueRainbow*)background)->setWaveShift(true);
        }

        void loop()
        {
            background->draw(display);
        }
};
