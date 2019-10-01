#pragma once

#include <Game.h>
#include <LifeAnimation.h>
#include <dirPad.h>

class LifeGameSinglePlayer : Game
{
	// Controls
	DirPad dirPad;

    // Animations
    LifeAnimation lifeGrid;

	long millisPerFrame = 50;
	const static long millisPerFrameStep = 5;
	long lastFrameMillis = 0;
	long nextDrawFrameMillis = 0;

	// Degrees per millisecond
	const static float hueShiftRate = 30.0f * (256.0f / 360.0f) / 1000.0f; // 30 deg/sec?
	int startHue;
	const vector<int> hueOffsets
	{	// Degrees are converted to int with result = degrees * 256 / 360
		0, // 0 deg
		43, // 60 deg
		128, // 180 deg
		213, // 300 deg
	};

	bool isPaused = false;

public:
    LifeGameSinglePlayer(Display* display) : Game(display),
		lifeGrid(display->numStrips + 2, display->lengthStrips),
		dirPad()
    {
    }

    void setup()
    {
        // start off randomized
        lifeGrid.randomize();
    }

    virtual void loop()
    {
		long timeDiff = millis() - lastFrameMillis;
		lastFrameMillis = millis();

		dirPad.pollAll();

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
			setHue((int)(startHue + hueShiftRate * timeDiff) % 256);
		}
		else if (dirPad.right.isPressed())
		{
			setHue((int)(256 + startHue - hueShiftRate * timeDiff) % 256);
		}

		Serial.println(millisPerFrame);

		// pause/play controls
		if (dirPad.a.isDepressing())
		{
			isPaused = !isPaused;
		}

		if (millis() >= nextDrawFrameMillis)
		{
			// randomize controls on frame speed
			if (dirPad.b.isPressed())
			{
				lifeGrid.randomize();
			}
			else if (isPaused == false)
			{
		        // Calculate next round
		        lifeGrid.GoOneRound();
			}

			nextDrawFrameMillis = millis() + millisPerFrame;
		}

        // Draw to display
        lifeGrid.draw(display);
    }

	void setHue(int hue)
	{
		startHue = hue;
		lifeGrid.ageColors.clear();
		lifeGrid.ageColors.push_back(CRGB::Black);
		for (int i = 0; i < hueOffsets.size(); i++)
		{
			CRGB color;
			color.setHSV((hue + hueOffsets[i]) % 256, 255, 255);
			lifeGrid.ageColors.push_back(color);
		}
	}
};
