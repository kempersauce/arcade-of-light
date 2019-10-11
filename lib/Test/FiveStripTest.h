#pragma once

#include <Game.h>
#include <Constants.h>
#include <SingleColorBG.h>
#include <Dot.h>

//Test for Directional Pad
class FiveStripTest : Game
{
    public:
        Dot* player;
        SingleColorBG* backgroundColor;

        FiveStripTest(Display* gameDisplay)
            : Game(gameDisplay)
        {
            
        }

        void setStrips()
        {
            // debug which strip is which
            for (int i = 0; i < display->lengthStrips; i++)
            {
                display->strips[0][i] = CRGB::Red;
                display->strips[1][i] = CRGB::Green;
                display->strips[2][i] = CRGB::Blue;
                display->strips[3][i] = CRGB::Yellow;
                display->strips[4][i] = CRGB::Violet;
            }
        }

        void setup()
        {
            setStrips();
        }

        void loop()
        {
            setStrips();
        }
};
