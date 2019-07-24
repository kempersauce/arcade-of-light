#include <Game.h>
#include <Constants.h>
#include <DirPad.h>

#define delayVal 25


//Rainbow Animation
class RainbowAni : Animation
{
    public:
        //override rainbow draw function
        void draw(Display* display){
            for (int i = 1; i < display->lengthStrips; i++)
            {
                for (int j = 0; j < display->numStrips; j++) {
                    display->strips[j][i] = rainbows[(i%7)+iterator];
                }
            }

            if (iterator < 6)
            {
                iterator++;
            }
            else
            {
                iterator = 0;
            }
        }

    private:
        CRGB rainbows[14] = {
          CRGB::Red,
          CRGB::Orange,
          CRGB::Yellow,
          CRGB::Green,
          CRGB::Blue,
          CRGB::Indigo,
          CRGB::Violet,
          CRGB::Red,
          CRGB::Orange,
          CRGB::Yellow,
          CRGB::Green,
          CRGB::Blue,
          CRGB::Indigo,
          CRGB::Violet
        };

        int iterator = 0;
};

//Rainbow Class
class GameBow : Game
{
    public:
        GameBow(Display* gameDisplay)
            : Game(gameDisplay)
        {
        }

        void setup()
        {
            background = (Animation*)new RainbowAni();
        }

        void loop()
        {
            background->draw(display);
            FastLED.show();
        }
};
