#include <Game.h>
#include <H2HDisplay.h>
#include <H2HControls.h>
#include <Noise.h>
#include <Charge.h>



class StartGame : Game
{
    public:
        H2HControls* controls;
        Charge** gameCharge;
        Noise* background;
        StartGame(Display* gameDisplay)
            : Game(gameDisplay)
        {
        background = new Noise(display->numStrips, display->lengthStrips);
        gameCharge = new Charge*[1];
        //Charge (int startHue, int startX, int startY, int yMaximum)
        gameCharge[0] = new Charge(0,1,display->lengthStrips,display->lengthStrips/2);
        gameCharge[1] = new Charge(160,1,0,display->lengthStrips/2);
        }

        void setup()
        {
            FastLED.setBrightness(50);
            controls = (H2HControls*)new H2HControls();

        }

        void loop()
        {
            controls->pollAll();
            background->draw(display);
            checkTeam(controls->teamA);
            checkTeam(controls->teamB);
            for (int i = 0; i < 2; i++)
            {
              gameCharge[i]->draw(display);
            }
            FastLED.show();
        }

        void checkTeam(Button** team)
        {
            for (int i = 0; i < 2; i++)
            {
                if (team[i]->isPressed())
                {
                  gameCharge[i]->power(true);
                } else {
                  gameCharge[i]->power(false);
                }

            }
        }


};
