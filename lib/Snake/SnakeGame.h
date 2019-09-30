
#pragma once

#include <Snake.h>

class SnakeGame : Game
{
	DirPad controls;
	Snake snake;
	SingleColorBG background;

public:
    SnakeGame(Display* gameDisplay)
		: Game(gameDisplay),
		controls(),
		snake(gameDisplay->numStrips, gameDisplay->lengthStrips),
		background(0, 0, 0)
    {
    }

    virtual void setup()
	{
		snake.Reset();
	}

    virtual void loop()
	{
		controls.pollAll();

		if (controls.up.isDepressing() && snake.currentDirection != Down)
		{
			snake.currentDirection = Up;
		}
		else if (controls.down.isDepressing() && snake.currentDirection != Up)
		{
			snake.currentDirection = Down;
		}
		else if (controls.left.isDepressing() && snake.currentDirection != Right)
		{
			snake.currentDirection = Left;
		}
		else if (controls.right.isDepressing() && snake.currentDirection != Left)
		{
			snake.currentDirection = Right;
		}

		if (controls.a.isPressed())
		{
			snake.Grow();
		}

		snake.Move();

		if (snake.head.first < 0 || snake.head.first >= display->numStrips
			|| snake.head.second < 0 || snake.head.second >= display->lengthStrips)
		{
			setup();
		}

		background.draw(display);
		snake.draw(display);
	}
};
