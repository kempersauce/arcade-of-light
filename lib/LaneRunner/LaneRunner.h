
#pragma once

#include <SingleColorBG.h>
#include <DirPad.h>
#include <PhysicsInfo.h>
#include <deque>

using namespace std;

class LaneRunnerGame : Game
{
	DirPad controls;
	PhysicsInfo player;
	SingleColorBG background;

	deque<int> dots;

public:
    LaneRunnerGame(Display* gameDisplay)
		: Game(gameDisplay),
		controls(),
		background(0, 0, 0),
		dots()
    {
    }

    virtual void setup()
	{
		player.xLocation = display->numStrips / 2;
		player.Location = display->lengthStrips * 2 / 3;

		// seed walls with initial stuff
		dots.clear();
		while (dots.size() < display->lengthStrips - 1)
		{
			dots.push_front(-1);
		}
	}

	void addDots()
	{
		bool anyDots = false;
		for (int i = 0; i < 10; i++)
		{
			if (dots[i] >= 0)
			{
				anyDots = true;
				break;
			}
		}

		dots.pop_back();
		if (anyDots)
		{
			dots.push_front(-1);
		}
		else
		{
			int lane = random16() / (UINT16_MAX / 3);
			switch (lane)
			{
				case 0:
					// nothing we'll keep this at 0
					lane = 0;
				break;

				case 1:
					lane = display->numStrips / 2;
				break;

				case 2:
					lane = display->numStrips - 1;
				break;

				default:
					lane = 1;
				break;
			}

			dots.push_front(lane);
		}
	}

    virtual void loop()
	{
		controls.pollAll();

		if (controls.up.isPressed())
		{
			player.Velocity = 20;
		}
		else if (controls.down.isPressed())
		{
			player.Velocity = -20;
		}
		else
		{
			player.Velocity = 0;
		}

		if (controls.left.isPressed())
		{
			player.xLocation = 0;
		}
		else if (controls.right.isPressed())
		{
			player.xLocation = display->numStrips - 1;
		}
		else
		{
			player.xLocation = display->numStrips / 2;
		}

		player.Move();
		if (player.Location < 0)
			player.Location = 0;
		else if (player.Location >= display->lengthStrips)
			player.Location = display->lengthStrips - 1;

		addDots();

		if ((int)player.xLocation == dots[(int)player.Location])
		{
			dots[(int)player.Location] = -1;
		}

		background.draw(display);

		// draw the dots
		for (int y = 0; y < display->lengthStrips; y++)
		{
			int lane = dots[y];
			if (lane >= 0)
			{
				display->strips[lane][y] = CRGB::Magenta;
			}
		}

		// draw player
		display->strips[(int)player.xLocation][(int)player.Location] = CRGB::Green;
	}
};
