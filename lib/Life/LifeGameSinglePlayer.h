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

	float millisPerFrame = 50;
	const static float millisPerFrameCoefficient = .9;
	long lastFrameMillis;

	// Degrees per millisecond
	const static float hueShiftRate = 30.0 * (256.0 / 360.0) / 1000.0; // 30 deg/sec?
	uint8_t startHue;
	const vector<uint8_t> hueOffsets
	{	// Degrees are converted to uint8_t with result = degrees * 256 / 360
		0, // 0 deg
		21, // 30 deg
		128, // 180 deg
		149, // 270 deg
	};

public:
    LifeGameSinglePlayer(Display* display) : Game(display),
		lifeGrid(display->numStrips * 2, display->lengthStrips),
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
		long m = millis();
		long timeDiff = m - lastFrameMillis;
		lastFrameMillis = m;

		dirPad.pollAll();

		// Speed adjust controls
		if (dirPad.up.isPressed())
		{
			millisPerFrame /= millisPerFrameCoefficient;
		}
		else if (dirPad.down.isPressed())
		{
			millisPerFrame *= millisPerFrameCoefficient;
		}

		// Hue adjust controls
		if (dirPad.left.isPressed())
		{
			setHue(startHue + hueShiftRate * timeDiff);
		}
		else if (dirPad.right.isPressed())
		{
			setHue(startHue - hueShiftRate * timeDiff);
		}

		if (dirPad.b.isPressed())
		{
			lifeGrid.randomize();
		}

		// Implement variable speed here
		// this game might not need this and could just use delay(millisPerFrame)
		// if we get frame skipping like, every other or so, then change this
		do
		{
	        // Calculate next round
	        lifeGrid.GoOneRound();
			timeDiff -= millisPerFrame;
		} while(timeDiff > 0);

        // Draw to display
        lifeGrid.draw(display);
    }

	void setHue(uint8_t hue)
	{
		lifeGrid.ageColors.clear();
		lifeGrid.ageColors.push_back(CRGB::Black);
		for (int i = 0; i < hueOffsets.size(); i++)
		{
			CRGB color;
			color.setHSV(hue + hueOffsets[i], 0, 255);
			lifeGrid.ageColors.push_back(color);
		}
	}
};
