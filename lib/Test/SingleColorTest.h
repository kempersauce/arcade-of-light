#include <Game.h>
#include <Display.h>
#include <SingleColorBG.h>


class SingleColorTest : Game
{
    public:
        SingleColorTest(Display* gameDisplay)
            : Game(gameDisplay)
        {
        }

        void setup()
        {
            FastLED.setBrightness(50);
            background = (Animation*)new SingleColorBG(0, 0, 255);
        }

        void loop()
        {
            background->draw(display);
        }
};
