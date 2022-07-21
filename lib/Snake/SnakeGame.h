
#pragma once

#include <Snake.h>

class SnakeGame : Game
{
	DirPad controls;
	Snake snake;
	SingleColorBG background;

public:
    SnakeGame(Display* gameDisplay, DirPad controls)
		: Game(gameDisplay),
		controls{std::move(controls)},
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
		if (controls.up->IsDepressing() && snake.currentDirection != Down)
		{
			snake.currentDirection = Up;
		}
		else if (controls.down->IsDepressing() && snake.currentDirection != Up)
		{
			snake.currentDirection = Down;
		}
		else if (controls.left->IsDepressing() && snake.currentDirection != Right)
		{
			snake.currentDirection = Left;
		}
		else if (controls.right->IsDepressing() && snake.currentDirection != Left)
		{
			snake.currentDirection = Right;
		}

		if (controls.a->IsPressed())
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
