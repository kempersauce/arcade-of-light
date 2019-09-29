#include <Game.h>
#include <Constants.h>
#include <Button.h>
#include <H2HDisplay.h>
#include <H2HControls.h>
#include <SingleColorBG.h>
#include <H2HDot.h>
#include <H2HZone.h>
#include <NoiseGenerator.h>
#include <H2HGameStrip.h>
#include <RainbowGame.h>

class Head2Head : Game
{
    NoiseGenerator* noiseGenerator;

    // Idle Game, plays after no buttons have been pressed before idle timeout
    RainbowGame idleGame;
    bool isIdle;
    const long idleTimeoutMillis = 1000 * 45; // 45 seconds

public:
    H2HGameStrip** gameStrips; // one for each strip

    Head2Head(Display* gameDisplay)
        : Game(gameDisplay),
        idleGame(gameDisplay)
    {
        noiseGenerator = new NoiseGenerator(gameDisplay->numStrips, gameDisplay->lengthStrips);

        // Initialize each game strip
        gameStrips = new H2HGameStrip*[gameDisplay->numStrips];

        // Do this one at a time so we can feed it pin numbers and button colors
        gameStrips[0] = new H2HGameStrip(0, gameDisplay->lengthStrips, H2H_BUTTON_PIN_7, H2H_BUTTON_PIN_8, noiseGenerator);
        gameStrips[1] = new H2HGameStrip(1, gameDisplay->lengthStrips, H2H_BUTTON_PIN_6, H2H_BUTTON_PIN_9, noiseGenerator);
        gameStrips[2] = new H2HGameStrip(2, gameDisplay->lengthStrips, H2H_BUTTON_PIN_5, H2H_BUTTON_PIN_10, noiseGenerator);
        gameStrips[3] = new H2HGameStrip(3, gameDisplay->lengthStrips, H2H_BUTTON_PIN_4, H2H_BUTTON_PIN_11, noiseGenerator);
        gameStrips[4] = new H2HGameStrip(4, gameDisplay->lengthStrips, H2H_BUTTON_PIN_3, H2H_BUTTON_PIN_12, noiseGenerator);
        gameStrips[5] = new H2HGameStrip(5, gameDisplay->lengthStrips, H2H_BUTTON_PIN_2, H2H_BUTTON_PIN_13, noiseGenerator);
        gameStrips[6] = new H2HGameStrip(6, gameDisplay->lengthStrips, H2H_BUTTON_PIN_1, H2H_BUTTON_PIN_14, noiseGenerator);
        gameStrips[7] = new H2HGameStrip(7, gameDisplay->lengthStrips, H2H_BUTTON_PIN_0, H2H_BUTTON_PIN_15, noiseGenerator);
    }

    void setup()
    {
        for (int i = 0; i < display->numStrips; i++)
        {
            gameStrips[i]->reset();
        }
    }

    void loop()
    {
        bool wasIdle = isIdle;
        isIdle = true;
        for (int i = 0; i < 8; i++)
        {
            gameStrips[i]->pollButtons();

            // if any buttons aren't past the idle timeout yet, then we're not idling
            if (gameStrips[i]->buttonA->getMillisReleased() <= idleTimeoutMillis
                || gameStrips[i]->buttonB->getMillisReleased() <= idleTimeoutMillis)
            {
                isIdle = false;
            }
        }


        if (isIdle)
        {
            // Reset the idle game if we're just entering idle
            if (wasIdle == false)
            {
                idleGame.setup();
            }

            // play the idle game, not this one
            idleGame.loop();
            return;
        }
        // Reset this game if we're just exiting idle
        else if (wasIdle)
        {
            this->setup();
        }

        // Generate noise
        noiseGenerator->fillnoise8();

        for (int i = 0; i < 8; i++)
        {
            gameStrips[i]->checkGameState();
        }

        for (int i = 0; i < 8; i++)
        {
            gameStrips[i]->draw(display);
        }

        if (H2HGameStrip::teamATotalWin || H2HGameStrip::teamBTotalWin)
        {
            // log when the win started
            static long totalWinStart = 0;
            if (totalWinStart == 0)
            {
                totalWinStart = millis();
            }
            // time to reset the whole game after 10 seconds
            else if (millis() - totalWinStart > 10000)
            {
                setup();
                totalWinStart = 0;
            }
        }
    }
};
