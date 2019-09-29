
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
		snake(),
		background(0, 0, 0)
    {
        display = gameDisplay;
    }

    virtual void setup()
	{
		snake.StartAt(display->numStrips / 2, display->lengthStrips / 2, Up);
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

		snake.Move();

		background.draw(display);
		snake.draw(display);
	}
};
