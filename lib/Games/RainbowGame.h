/*
Game class
Where the magic happens
*/

#pragma once

#include <HueRainbow.h>

class RainbowGame : Game
{
	HueRainbow background;

public:

    RainbowGame(Display* gameDisplay)
        : Game(gameDisplay),
		background(2)
    {
      	background.setWaveShift(true);
    }

    void setup()
    {
    }

    void loop()
    {
        background.draw(display);
    }
};
