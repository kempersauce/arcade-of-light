#pragma once

#include <Game.h>
#include <Constants.h>
#include <Flicker.h>
#include <SingleColorBG.h>

//Test for Directional Pad
class AnimationTest : Game
{
    public:
        Flicker* flicker;
        SingleColorBG* bg;

        AnimationTest(Display* gameDisplay)
            : Game(gameDisplay)
        {
            
        }

        void setup()
        {
            flicker = new Flicker(12, 8, 0, 55);
            bg = new SingleColorBG(200,0,0);
        }

        void loop()
        {
            bg->draw(display);
            flicker->draw(display);
        }
};
