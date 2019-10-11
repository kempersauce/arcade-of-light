/*
Game class
Where the magic happens
*/

#pragma once

#include <HueRainbow.h>
//#include <AudioSender.h>

class RainbowGame : Game
{
	HueRainbow background;
    //AudioSender* audio;

public:

    RainbowGame(Display* gameDisplay)
        : Game(gameDisplay),
		background(2)
    {
      	background.setWaveShift(true);
    }

    void setup()
    {
        // audio = new AudioSender();
        // audio->playIdleBG();
    }

    void loop()
    {
        background.draw(display);
    }
};
