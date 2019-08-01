#include <Game.h>
#include <H2HDisplay.h>

class H2HRainbowAni : Animation
{
    public:
        //override rainbow draw function
        void draw(Display* display){
            // for (int i = 0; i < display->lengthStrips; i++)
            // {
            //     for (int j = 0; j < display->numStrips; j++) {
            //         display->strips[j][i] = rainbows[(i%7)+iterator];
            //     }
            // }
            //
            // if (iterator < 6)
            // {
            //     iterator++;
            // }
            // else
            // {
            //     iterator = 0;
            // }

            //static colors for pin numbering test
            for (int i = 0; i < display->lengthStrips; i++)
            {
                for (int j = 0; j < display->numStrips; j++) {
                    display->strips[j][i] = rainbows[j];
                }
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


class H2HTest : Game
{
    public:
        H2HTest(Display* gameDisplay)
            : Game(gameDisplay)
        {
        }

        void setup()
        {
            background = (Animation*)new H2HRainbowAni();
        }

        void loop()
        {
            background->draw(display);
            FastLED.setBrightness(50);
            FastLED.show();
        }
};
