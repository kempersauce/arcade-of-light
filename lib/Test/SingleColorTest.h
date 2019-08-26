#include <Game.h>
#include <SingleColorBG.h>


class SingleColorTest : Game
{
    public:
        SingleColorTest(Display* gameDisplay)
            : Game(gameDisplay)
        {
            background = (Animation*)new SingleColorBG(0, 0, 255);
        }

        void setup()
        {
        }

        void loop()
        {
            background->draw(display);
        }
};
