#include <Game.h>
#include <Constants.h>
#include <button.h>
#include <H2HDisplay.h>
#include <H2HControls.h>
#include <SingleColorBG.h>
#include <H2HDot.h>
#include <H2HZone.h>
#include <NoiseGenerator.h>
#include <H2HGameStrip.h>
#include <RainbowGame.h>
#include <LifeGame.h>
#include <ElectricArc.h>
#include <H2HAudio.h>

enum H2HGameState
{
	H2HGameIdle,
	H2HGameStart,
	H2HGamePlaying,
	H2HGameWinA,
	H2HGameWinB,
};

class Head2Head : Game
{
	H2HGameState gameState;

    NoiseGenerator noiseGenerator;

	ElectricArc electricArc;

    // Idle Game, plays after no buttons have been pressed before idle timeout
    RainbowGame idleGame;
    bool isIdle;
    const static long idleTimeoutMillis = 1000 * 45; // 45 seconds

	long totalWinStart = 0; // timer for win state
	const static long totalWinTimeoutMillis = 1000 * 10; // 10 seconds in win state

	H2HAudio* audio;
	bool isFirstSetup = true;

public:
    H2HGameStrip** gameStrips; // one for each strip

    Head2Head(Display* gameDisplay)
        : Game(gameDisplay),
        idleGame(gameDisplay),
		noiseGenerator(gameDisplay->numStrips, gameDisplay->lengthStrips),
		electricArc()
    {
		noiseGenerator.speed = 30;

        // Initialize each game strip
        gameStrips = new H2HGameStrip*[gameDisplay->numStrips];

        // Do this one at a time so we can feed it pin numbers and button colors
        gameStrips[0] = new H2HGameStrip(0, gameDisplay->lengthStrips, H2H_BUTTON_PIN_7, H2H_BUTTON_PIN_8, &noiseGenerator);
        gameStrips[1] = new H2HGameStrip(1, gameDisplay->lengthStrips, H2H_BUTTON_PIN_6, H2H_BUTTON_PIN_9, &noiseGenerator);
        gameStrips[2] = new H2HGameStrip(2, gameDisplay->lengthStrips, H2H_BUTTON_PIN_5, H2H_BUTTON_PIN_10, &noiseGenerator);
        gameStrips[3] = new H2HGameStrip(3, gameDisplay->lengthStrips, H2H_BUTTON_PIN_4, H2H_BUTTON_PIN_11, &noiseGenerator);
        gameStrips[4] = new H2HGameStrip(4, gameDisplay->lengthStrips, H2H_BUTTON_PIN_3, H2H_BUTTON_PIN_12, &noiseGenerator);
        gameStrips[5] = new H2HGameStrip(5, gameDisplay->lengthStrips, H2H_BUTTON_PIN_2, H2H_BUTTON_PIN_13, &noiseGenerator);
        gameStrips[6] = new H2HGameStrip(6, gameDisplay->lengthStrips, H2H_BUTTON_PIN_1, H2H_BUTTON_PIN_14, &noiseGenerator);
        gameStrips[7] = new H2HGameStrip(7, gameDisplay->lengthStrips, H2H_BUTTON_PIN_0, H2H_BUTTON_PIN_15, &noiseGenerator);
    }

    void setup()
    {
		if(isFirstSetup)
		{
			audio = new H2HAudio();
			isFirstSetup = false;
			
		}
		enterStartState();
		//enterWinBState();
    }

	void enterStartState()
	{
		gameState = H2HGameStart;
		audio->playStdBG();
		audio->stopWinMusic();
		//dont forget to take this out lol
		audio->itsTimeToDuel();
        for (int i = 0; i < display->numStrips; i++)
        {
            gameStrips[i]->reset();
        }
	}

	void enterPlayingState()
	{
		gameState = H2HGamePlaying;
	}

	void enterWinAState()
	{
		audio->playTeamAWinGame();
		gameState = H2HGameWinA;
		for (int i = 0; i < display->numStrips; i++)
		{
			gameStrips[i]->enterTotalWinAState();
		}
		totalWinStart = millis();
	}

	void enterWinBState()
	{
		audio->playTeamBWinGame();
		gameState = H2HGameWinB;
		for (int i = 0; i < display->numStrips; i++)
		{
			gameStrips[i]->enterTotalWinBState();
		}
		totalWinStart = millis();
	}

	void enterIdleState()
	{
		gameState = H2HGameIdle;
		idleGame.setup();
	}

    void loop()
    {
        bool isIdle = true;
        for (int i = 0; i < display->numStrips; i++)
        {
            gameStrips[i]->pollButtons();

            // if any buttons aren't past the idle timeout yet, then we're not idling
            if (gameStrips[i]->buttonA.GetMillisReleased() <= idleTimeoutMillis
                || gameStrips[i]->buttonB.GetMillisReleased() <= idleTimeoutMillis)
            {
                isIdle = false;
            }
        }

		// Switch to idling if we're not already doing it
        if (gameState != H2HGameIdle && isIdle)
        {
			enterIdleState();
        }

        // Start a new game when we come out of idle
        else if (gameState == H2HGameIdle && isIdle == false)
        {
            enterStartState();
        }

		// Play the game for one round according to game state
		switch (gameState)
		{
			case H2HGameIdle:
				idleGame.loop();
			break;

			case H2HGameStart:
				// Go straight into playing for now until we have something here
				enterPlayingState();
			//break;  // Uncomment this once we have something for start game

			case H2HGamePlaying:
		        // Generate noise
		        noiseGenerator.fillnoise8();

		        for (int i = 0; i < display->numStrips; i++)
		        {
		            gameStrips[i]->checkGameState(audio);
		        }

		        for (int i = 0; i < display->numStrips; i++)
		        {
		            if (gameStrips[i]->stripState == H2HStripTotalWinA)
					{
						enterWinAState();
						break;
					}
					else if (gameStrips[i]->stripState == H2HStripTotalWinB)
					{
						enterWinBState();
						break;
					}
		        }
			break;

			case H2HGameWinA:
		        // Generate noise
		        noiseGenerator.fillnoise8();
				H2HGameStrip::midBar++;

				if (millis() - totalWinStart > totalWinTimeoutMillis)
	            {
					enterStartState();
	            }
			break;

			case H2HGameWinB:
		        // Generate noise
		        noiseGenerator.fillnoise8();
				H2HGameStrip::midBar--;

				if (millis() - totalWinStart > totalWinTimeoutMillis)
	            {
					enterStartState();
	            }
			break;
		}

		// Draw the game according to game state
		switch (gameState)
		{
			case H2HGameIdle:
				// Do nothing here - idleGame already did it
			break;

			case H2HGameStart:
				// ??
			break;

			case H2HGamePlaying:
			case H2HGameWinA:
			case H2HGameWinB:
				for (int i = 0; i < display->numStrips; i++)
				{
					gameStrips[i]->draw(display);
				}
				electricArc.yLocation = H2HGameStrip::midBar;
				electricArc.draw(display);
			break;
		}
    }
};
