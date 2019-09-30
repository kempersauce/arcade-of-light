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
            gameCharge = new Charge*[2];
            //Charge (int startHue, int startX, int startY, int yMaximum)
            gameCharge[0] = new Charge(0, 1, display->lengthStrips, display->lengthStrips / 2);
            gameCharge[1] = new Charge(160, 1, 0, display->lengthStrips / 2);
        }

        void setup()
        {
            controls = (H2HControls*)new H2HControls();
        }

        void loop()
        {
            controls->pollAll();
            background->draw(display);
            checkTeam(controls->teamA, gameCharge[0]);
            checkTeam(controls->teamB, gameCharge[1]);
            for (int i = 0; i < 2; i++)
            {
                gameCharge[i]->draw(display);
            }
        }

        void checkTeam(Button** team, Charge* charge)
        {
            charge->power(team[0]->isPressed());
        }
};
