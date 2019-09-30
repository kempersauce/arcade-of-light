#pragma once

#include <Game.h>
#include <Constants.h>
#include <Flicker.h>
#include <SingleColorBG.h>
#include <SingleColorBlock.h>

//Test for Directional Pad
class AnimationTest : Game
{
    public:
        Flicker* flicker;
        SingleColorBG* bg;
        SingleColorBlock* block;

        AnimationTest(Display* gameDisplay)
            : Game(gameDisplay)
        {
            
        }

        void setup()
        {
            flicker = new Flicker(100, 10, display->numStrips,0, 55);
            bg = new SingleColorBG(0,55,0);
            block = new SingleColorBlock(0, 100, 0, 255, 255);
        }

        void loop()
        {
            bg->draw(display);
            block->draw(display);
            flicker->draw(display);
        }
};
