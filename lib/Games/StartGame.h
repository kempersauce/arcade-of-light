#include <Game.h>
#include <H2HDisplay.h>
#include <H2HControls.h>
#include <Noise.h>
#include <Dot.h>



class H2HStartGame : Game
{
    public:
  //      H2HControls* controls;

        int DotPercentage[3];


        H2HTest(Display* gameDisplay)
            : Game(gameDisplay)

//brackets used to live here {}

        void setup()
        {
            FastLED.setBrightness(50);
            controls = (H2HControls*)new H2HControls();
            background = (Animation*)new Noise();
            dots = new H2HDot*[3] {
                //new H2HDot(CRGB::Purple, 0, 15, 8, 120),
                new H2HDot(CRGB::Red, 3, 15, 8, 0),
                new H2HDot(CRGB::Red, 4, 15, 8, 0),
                new H2HDot(CRGB::Blue, 3, 15, 8, 120),
                new H2HDot(CRGB::Blue, 4, 15, 8, 120),
                //new H2HDot(CRGB::Purple, 5, 15, 8, 120),
                //new H2HDot(CRGB::Purple, 6, 15, 8, 120),
                //new H2HDot(CRGB::Purple, 7, 15, 8, 120),
            };
        }

        void loop()
        {
            controls->pollAll();
            background->draw(display);
            checkTeam(controls->teamA, CRGB::Green, CRGB::Blue, true);
            checkTeam(controls->teamB, CRGB::Yellow, CRGB::Red, false);
            drawDots();
            fillStrip();
            setBackgroundBrightness();
            FastLED.show();
        }

        void checkTeam(Button** team, CRGB color1, CRGB color2, bool moveUp)
        {
            for (int i = 0; i < 2; i++)
            {
                if (team[i]->isPressed())
                {
                    for (int j = 0; j < dots[i]->yLoc; j++)
                    {
                        display->strips[i][j] = color2;
                        }
                    }
                    if(moveUp)
                    {
                        if dots[i] > display->lengthStrips / 2 {
                        dots[i]->move(0,1);
                      }
                    }else{
                        dots[i]->move(0,-1);
                    }
                    for (int j = 0; j < display->lengthStrips; j++)
                    // {
                    //     if(j<dots[i]->yLoc)
                    //     {
                    //         display->strips[i][j] = CRGB::Blue;
                    //     }
                    //     if(j>dots[i]->yLoc)
                    //     {
                    //         display->strips[i][j] = CRGB::Red;
                    //     }
                    // }

                }

            }
        }
        //fill the strip up to the
        void fillStrip()
        {

        }
        void drawDots()
        {
            for(int i=0; i<4; i++)
            {
                dots[i]->draw(display);
            }
        }
        void setBackgroundBrightness()
        {
            for(int i=0; i<4; i++)
            {
                DotPercentage[i] = dots[i]->yLoc / (display->lengthStrips / 2);
            }
            background->setBrightness(DotPercentage[0]+DotPercentage[1]+DotPercentage[2]+DotPercentage[3]/4*255);
        }

};
