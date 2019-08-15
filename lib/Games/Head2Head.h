#include <Game.h>
#include <Constants.h>
#include <Button.h>
#include <H2HDisplay.h>
#include <H2HControls.h>
#include <SingleColorBG.h>
#include <H2HDot.h>
#include <H2HZone.h>


class Head2Head : Game
{
    public:

        H2HDot** dots;
        H2HControls* controls;
        H2HZone** zoneA;
        H2HZone** zoneB;

        Head2Head(Display* gameDisplay)
            : Game(gameDisplay)
        {
        }

        void setup()
        {
            FastLED.setBrightness(50);
            
            controls = (H2HControls*)new H2HControls();
            background = (Animation*)new SingleColorBG(25,25,0);
            dots = new H2HDot*[8] {
                new H2HDot(CRGB::Purple, 0, 15, 8, 120),
                new H2HDot(CRGB::Purple, 1, 15, 8, 120),
                new H2HDot(CRGB::Purple, 2, 15, 8, 120),
                new H2HDot(CRGB::Purple, 3, 15, 8, 120),
                new H2HDot(CRGB::Purple, 4, 15, 8, 120),
                new H2HDot(CRGB::Purple, 5, 15, 8, 120),
                new H2HDot(CRGB::Purple, 6, 15, 8, 120),
                new H2HDot(CRGB::Purple, 7, 15, 8, 120),
            };

            zoneA = new H2HZone*[8] {
                new H2HZone(CRGB::Blue, 0, 5, 15),
                new H2HZone(CRGB::Blue, 1, 5, 15),
                new H2HZone(CRGB::Blue, 2, 5, 15),
                new H2HZone(CRGB::Blue, 3, 5, 15),
                new H2HZone(CRGB::Blue, 4, 5, 15),
                new H2HZone(CRGB::Blue, 5, 5, 15),
                new H2HZone(CRGB::Blue, 6, 5, 15),
                new H2HZone(CRGB::Blue, 7, 5, 15)
            };

            zoneB = new H2HZone*[8] {
                new H2HZone(CRGB::Red, 0, 105, 115),
                new H2HZone(CRGB::Red, 1, 105, 115),
                new H2HZone(CRGB::Red, 2, 105, 115),
                new H2HZone(CRGB::Red, 3, 105, 115),
                new H2HZone(CRGB::Red, 4, 105, 115),
                new H2HZone(CRGB::Red, 5, 105, 115),
                new H2HZone(CRGB::Red, 6, 105, 115),
                new H2HZone(CRGB::Red, 7, 105, 115)
            };

        }

        void loop()
        {
            controls->pollAll();
            background->draw(display);
            checkTeam(controls->teamA, CRGB::Green, CRGB::Blue, true);
            checkTeam(controls->teamB, CRGB::Yellow, CRGB::Red, false);
            allMove();
            drawZones();
            drawDots();
        }

        void allMove()
        {
            for (int i = 0; i < 8; i++)
            {
                dots[i]->vMove();
            }
        }

        void checkTeam(Button** team, CRGB color1, CRGB color2, bool moveUp)
        {
            for (int i = 0; i < 8; i++)
            {
                if (team[i]->isPressed())
                {
                    for (int j = 0; j < display->lengthStrips; j++)
                    {
                        if (i == 0 || i == 2 || i == 5 || i == 7)
                        {
                            display->strips[i][j] = color1;
                        }
                        else
                        {
                            display->strips[i][j] = color2;
                        }
                    }

                    if (zoneA[i]->checkZone(dots[i]->xLoc, dots[i]->yLoc))
                    {
                        dots[i]->velocity = 3;
                    }
                    else if (zoneB[i]->checkZone(dots[i]->xLoc, dots[i]->yLoc))
                    {
                        dots[i]->velocity = -3;
                    }

                    for (int j = 0; j < display->lengthStrips; j++)
                    {
                        if (j < dots[i]->yLoc)
                        {
                            display->strips[i][j] = CRGB::Blue;
                        }

                        if (j > dots[i]->yLoc)
                        {
                            display->strips[i][j] = CRGB::Red;
                        }
                    }
                }
            }
        }

        void drawDots()
        {
            for (int i = 0; i < 8; i++)
            {
                dots[i]->draw(display);
            }
        }

        void drawZones()
        {
            for (int i = 0; i < 8; i++)
            {
                zoneA[i]->draw(display);
                zoneB[i]->draw(display);
            }
        }
};
