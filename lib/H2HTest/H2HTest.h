#include <H2HGame.h>

class H2HRainbowAni : H2HAnimation
{
    public:
        //override rainbow draw function
        void draw(H2HDisplay* display){
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


class H2HTest : H2HGame
{
    public:
        H2HTest(H2HDisplay* gameDisplay)
            : H2HGame(gameDisplay)
        {
        }

        void setup()
        {
            background = (H2HAnimation*)new H2HRainbowAni();
        }

        void loop()
        {
            background->draw(display);
            FastLED.show();
        }
};
