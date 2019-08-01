#include <Game.h>
#include <H2HDisplay.h>
#include <Button.h>

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

    Button** teamA;
    Button** teamB;
    public:
        H2HTest(Display* gameDisplay)
            : Game(gameDisplay)
        {
        }

        void setup()
        {
            teamA = new Button*[8] {
                new Button(H2H_BUTTON_PIN_0),
                new Button(H2H_BUTTON_PIN_1),
                new Button(H2H_BUTTON_PIN_2),
                new Button(H2H_BUTTON_PIN_3),
                new Button(H2H_BUTTON_PIN_4),
                new Button(H2H_BUTTON_PIN_5),
                new Button(H2H_BUTTON_PIN_6),
                new Button(H2H_BUTTON_PIN_7),
            };

            teamB = new Button*[8] {
                new Button(H2H_BUTTON_PIN_8),
                new Button(H2H_BUTTON_PIN_9),
                new Button(H2H_BUTTON_PIN_10),
                new Button(H2H_BUTTON_PIN_11),
                new Button(H2H_BUTTON_PIN_12),
                new Button(H2H_BUTTON_PIN_13),
                new Button(H2H_BUTTON_PIN_14),
                new Button(H2H_BUTTON_PIN_15),
            };

            background = (Animation*)new H2HRainbowAni();
        }

        void loop()
        {
            pollAll();

            checkTeam(teamA, CRGB::Red);
            checkTeam(teamB, CRGB::Cyan);

            background->draw(display);
            FastLED.setBrightness(50);
            FastLED.show();
        }

        void checkTeam(Button** team, CRGB color)
        {
            for (int i = 0; i < 8; i++)
            {
                if (team[i]->isPressed())
                {
                    for (int j = 0; j < display->lengthStrips; j++)
                    {
                        display->strips[i][j] = color;
                    }
                }
            }
        }

        void pollAll()
        {
            for (int i = 0; i < 8; i++)
            {
                teamA[i]->poll();
                teamB[i]->poll();
            }
        }
};
