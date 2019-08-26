#include <Noise.h>
#include <Game.h>

class NoiseGame : Game
{
    Noise* noise;
    public:
        NoiseGame(Display* gameDisplay)
            : Game(gameDisplay)
        {
            noise = new Noise(display->numStrips, display->lengthStrips);
        }

        void setup()
        {
        }

        void loop()
        {
            noise->draw(display);
        }
};
