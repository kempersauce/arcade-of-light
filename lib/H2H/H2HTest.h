#include <Game.h>
#include <H2HDisplay.h>
#include <H2HControls.h>
#include <Dot.h>


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
            // for (int i = 0; i < display->lengthStrips; i++)
            // {
            //     for (int j = 0; j < display->numStrips; j++) {
            //         display->strips[j][i].setRGB(0,0,0);
            //     }
            // }
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

class H2HDot : public Dot
{
    public:
        int velocity;

        H2HDot(CRGB startColor, int startX, int startY, int startZ, int xMaximum, int yMaximum)
        :Dot(startColor, startX, startY, startZ, xMaximum, yMaximum)
        {
            velocity = 0;
        }
};

class H2HTest : Game
{
    public:
        H2HDot** dots;
        H2HControls* controls;

        H2HTest(Display* gameDisplay)
            : Game(gameDisplay)
        {
        }

        void setup()
        {
            controls = (H2HControls*)new H2HControls();
            background = (Animation*)new H2HRainbowAni();
            dots = new H2HDot*[8] {
                new H2HDot(CRGB::Purple, 0, 15, 0, 8, 120),
                new H2HDot(CRGB::Purple, 1, 15, 0, 8, 120),
                new H2HDot(CRGB::Purple, 2, 15, 0, 8, 120),
                new H2HDot(CRGB::Purple, 3, 15, 0, 8, 120),
                new H2HDot(CRGB::Purple, 4, 15, 0, 8, 120),
                new H2HDot(CRGB::Purple, 5, 15, 0, 8, 120),
                new H2HDot(CRGB::Purple, 6, 15, 0, 8, 120),
                new H2HDot(CRGB::Purple, 7, 15, 0, 8, 120),
            };
        }

        void loop()
        {
            controls->pollAll();
            background->draw(display);
            checkTeam(controls->teamA, CRGB::Green, CRGB::Blue, true);
            checkTeam(controls->teamB, CRGB::Yellow, CRGB::Red, false);
            drawDots();
            FastLED.setBrightness(50);
            FastLED.show();
        }

        void checkTeam(Button** team, CRGB color1, CRGB color2, bool moveUp)
        {
            for (int i = 0; i < 8; i++)
            {
                if (team[i]->isPressed())
                {
                    for (int j = 0; j < display->lengthStrips; j++)
                    {
                        if(i==0||i==2||i==5||i==7){
                            display->strips[i][j] = color1;
                        }else{
                            display->strips[i][j] = color2;
                        }
                    }
                    if(moveUp)
                    {
                        dots[i]->move(0,1);
                    }else{
                        dots[i]->move(0,-1);
                    }
                    for (int j = 0; j < display->lengthStrips; j++)
                    {
                        if(j<dots[i]->yLoc)
                        {
                            display->strips[i][j] = CRGB::Blue;
                        }
                        if(j>dots[i]->yLoc)
                        {
                            display->strips[i][j] = CRGB::Red;
                        }
                    }

                }

            }
        }
        void drawDots()
        {
            for(int i=0; i<8; i++)
            {
                dots[i]->draw(display);
            }
        }

};
