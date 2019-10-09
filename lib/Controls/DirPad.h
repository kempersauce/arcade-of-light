
#pragma once

#include <Button.h>
#include <PinSetup.h>

class DirPad
{
public:
    Button up;
    Button down;
    Button left;
    Button right;
    Button a;
    Button b;

    DirPad() :
		up(BUTTON_PIN_2),
		down(BUTTON_PIN_5),
		left(BUTTON_PIN_4),
		right(BUTTON_PIN_3),
		a(BUTTON_PIN_0),
		b(BUTTON_PIN_1)
    {
    }

    void pollAll()
	{
        up.poll();
        down.poll();
        left.poll();
        right.poll();
        a.poll();
        b.poll();
    }

	bool isIdle(long idleTimeout)
	{
		return up.getMillisReleased() >= idleTimeout
			&& down.getMillisReleased() >= idleTimeout
			&& left.getMillisReleased() >= idleTimeout
			&& right.getMillisReleased() >= idleTimeout
			&& a.getMillisReleased() >= idleTimeout
			&& b.getMillisReleased() >= idleTimeout;
	}
};
