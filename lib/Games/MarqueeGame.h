/*
Game class
Where the magic happens
*/

#pragma once

#include <Marquee.h>
#include <HueRainbow.h>

class MarqueeGame : Game
{
    public:

        Marquee* marquee;

        MarqueeGame(Display* gameDisplay)
            : Game(gameDisplay)
        {
            background = new HueRainbow(2);
            marquee = new Marquee(1);
        }

        void setup()
        {
          ((HueRainbow*)background)->setBrightness(150);
          ((HueRainbow*)background)->setSaturation(255);
        }

        void loop()
        {
            background->draw(display);
            marquee->draw(display);
        }
};
