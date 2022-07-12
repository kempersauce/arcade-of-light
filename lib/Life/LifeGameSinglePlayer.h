#pragma once

#include <Game.h>
#include <LifeAnimation.h>
#include <dirPad.h>
#include <RainbowGame.h>
#include <LifeAudio.h>

enum LifeGameState
{
	LifeGameIdle,
	LifeGamePlaying
};

class LifeGameSinglePlayer : Game
{
	// Controls
	DirPad dirPad;

    // Animations
    LifeAnimation lifeGrid;

	// Sound
	LifeAudio* audio;
	bool isFirstSetup = true;;

	long millisPerFrame = 50;
	const static long millisPerFrameStep = 5;
	long lastFrameMillis = 0;
	long nextDrawFrameMillis = 0;

	// Degrees per millisecond
	const static float hueShiftRate = 60.0f * (256.0f / 360.0f) / 1000.0f; // 60 deg/sec?
	float startHue;
	const vector<int> hueOffsets
	{	// Degrees are converted to int with result = degrees * 256 / 360
		0, // 0 deg
		43, // 60 deg
		128, // 180 deg
		213, // 300 deg
	};

	bool isPaused = false;

	LifeGameState gameState;

	const static long idleTimeoutMillis = 1000 * 90; // 90 seconds
	RainbowGame idleGame;

public:
    LifeGameSinglePlayer(Display* display, DirPad controls)
		: Game(display),
		idleGame(display),
		lifeGrid(display->numStrips + 1, display->lengthStrips),
		dirPad{std::move(controls)}
    {
    }

    void setup()
    {
		if(isFirstSetup)
		{
			audio = new LifeAudio();
			isFirstSetup = false;
			audio->playStdBG();
		}

		//Start BG music
		

		// Start off on blue
		setHue(140);

		

        // start off randomized
        lifeGrid.randomize();

		enterPlayingState();
    }

	void enterPlayingState()
	{
		gameState = LifeGamePlaying;
		audio->playStdBG();
	}

	void enterIdleState()
	{
		gameState = LifeGameIdle;
		idleGame.setup();
	}

    virtual void loop()
    {
		long timeDiff = millis() - lastFrameMillis;
		lastFrameMillis = millis();

		bool isIdle = dirPad.isIdle(idleTimeoutMillis);

		// Switch to idling if we're not already doing it
        if (gameState != LifeGameIdle && isIdle)
        {
			enterIdleState();
        }

        // Start a new game when we come out of idle
        else if (gameState == LifeGameIdle && isIdle == false)
        {
            enterPlayingState();
        }

		if (gameState == LifeGameIdle)
		{
			idleGame.loop();
			return;
		}

		// Speed adjust controls
		if (dirPad.up.isPressed())
		{
			millisPerFrame += (float)millisPerFrame / (float)20;
		}

		if (dirPad.down.isPressed())
		{
			millisPerFrame -= (float)millisPerFrame / (float)20;
		}

		if (millisPerFrame < 20)
		{
			millisPerFrame = 20;
		}
		else if (millisPerFrame > 1000)
		{
			millisPerFrame = 1000;
		}

		// Hue adjust controls
		if (dirPad.left.isPressed())
		{
			setHue(startHue + hueShiftRate * timeDiff);
			//audio->playColorShift();
		}
		else if (dirPad.right.isPressed())
		{
			setHue(startHue - hueShiftRate * timeDiff);
			//audio->playColorShift();
		}
		else
		{
			//audio->stopColorShift();
		}
		

		// pause/play controls
		if (dirPad.a.isDepressing())
		{
			isPaused = !isPaused;
			if(isPaused == true)
			{
				// audio->playTimeStop();
			}
			else
			{
				// audio->playTimeStart();
			}
			
		}

		if (millis() >= nextDrawFrameMillis)
		{
			// randomize controls on frame speed
			if (dirPad.b.isPressed())
			{
				// if(!audio->shuffleIsStarted)
				// {
				// 	audio->startRandom();
				// }
				lifeGrid.randomize();
			}
			else if (isPaused == false)
			{
		        // Calculate next round
		        lifeGrid.GoOneRound();
			}
			// if(dirPad.b.isUp() && audio->shuffleIsStarted)
			// {
			// 	audio->stopPlayRandom();
			// }

			nextDrawFrameMillis = millis() + millisPerFrame;
		}

        // Draw to display
        lifeGrid.draw(display);
    }

	void setHue(float hue)
	{
		startHue = hue;
		if (startHue >= 256)
		{
			startHue -= 256;
		}
		else if (startHue < 0)
		{
			startHue += 256;
		}

		lifeGrid.ageColors.clear();
		lifeGrid.ageColors.push_back(CRGB::Black);
		for (int i = 0; i < hueOffsets.size(); i++)
		{
			CRGB color;
			color.setHSV(((int)startHue + hueOffsets[i]) % 256, 255, 255);
			lifeGrid.ageColors.push_back(color);
		}
	}
};
