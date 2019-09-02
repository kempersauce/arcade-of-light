/*
Game class
Where the magic happens
*/

#pragma once

#include <Marquee.h>

class MarqueeGame : Game
{
    public:

        MarqueeGame(Display* gameDisplay)
            : Game(gameDisplay)
        {
            background = new Marquee(1, 200, 1, 20);
        }

        void setup()
        {
          //((HueRainbow*)background)->setWaveShift(true);
        }

        void loop()
        {
            background->draw(display);
        }
};
