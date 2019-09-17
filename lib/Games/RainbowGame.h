/*
Game class
Where the magic happens
*/

#pragma once

#include <HueRainbow.h>

class RainbowGame : Game
{
    HueRainbow* background;
    
    public:

        RainbowGame(Display* gameDisplay)
            : Game(gameDisplay)
        {
            background = new HueRainbow(2);
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
