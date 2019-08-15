#include <Game.h>
#include <Constants.h>
#include <SingleColorBG.h>
#include <Dot.h>
#include <DirPad.h>

//Test for Directional Pad
class DirPadTest : Game
{
    public:
        DirPad* controls;
        Dot* player;
        SingleColorBG* backgroundColor;

        DirPadTest(Display* gameDisplay)
            : Game(gameDisplay)
        {
        }

        void setup()
        {
            //background = (Animation*)new SingleColorBG(0,0,55);
            backgroundColor = new SingleColorBG(0, 0, 55);
            player = (Dot*)new Dot(55, 0, 0, 4, 0, 1,
                display->numStrips, display->lengthStrips);

            controls = new DirPad();
        }

        void loop()
        {
            controls->pollAll();

            if (controls->up->isPressed())
            {
                backgroundColor->setColor(0, 55, 0);
            }

            if (controls->down->isPressed())
            {
                backgroundColor->setColor(55, 0, 0);
            }

            if (controls->left->isPressed())
            {
                backgroundColor->setColor(0, 0, 55);
            }

            if (controls->right->isPressed())
            {
                backgroundColor->setColor(55 ,55, 0);
            }

            if (controls->a->isPressed())
            {
                backgroundColor->setColor(0, 55, 55);
            }

            if (controls->b->isPressed())
            {
                backgroundColor->setColor(0, 55, 55);
            }


            backgroundColor->draw(display);
            player->draw(display);
            FastLED.show();
        }
};
