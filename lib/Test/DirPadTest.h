#pragma once

#include <Game.h>
#include <Constants.h>
#include <SingleColorBG.h>
#include <Dot.h>
#include <DirPad.h>
#include <HueRainbow.h>

//Test for Directional Pad
class DirPadTest : Game
{
    public:
        DirPad* controls;
        Dot* player;
        SingleColorBG* backgroundColor;
        HueRainbow* rainbow;

        DirPadTest(Display* gameDisplay)
            : Game(gameDisplay)
        {
            rainbow = new HueRainbow(1);
        }

        void setup()
        {
            player = (Dot*)new Dot(CRGB::Green, 5, 5,
                display->numStrips, display->lengthStrips);

            controls = new DirPad();
            rainbow->setWaveShift(true);
        }

        void loop()
        {
            controls->pollAll();

            if (controls->up->isPressed())
            {
                
            }

            if (controls->down->isPressed())
            {
                
            }

            if (controls->left->isPressed())
            {
                
            }

            if (controls->right->isPressed())
            {
                
            }

            if (controls->a->isPressed())
            {
                
            }

            if (controls->b->isPressed())
            {
                
            }


            rainbow->draw(display);
            player->draw(display);
            FastLED.show();

        }
};
