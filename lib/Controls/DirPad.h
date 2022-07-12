
#pragma once

#include <memory>  // For shared_ptr

#include <button.h>  // For Button
#include <PinSetup.h>

class DirPad
{
  public:
    std::shared_ptr<Button> up;
    std::shared_ptr<Button> down;
    std::shared_ptr<Button> left;
    std::shared_ptr<Button> right;
    std::shared_ptr<Button> a;
    std::shared_ptr<Button> b;

    DirPad(std::shared_ptr<Button> up,
            std::shared_ptr<Button> down,
            std::shared_ptr<Button> left,
            std::shared_ptr<Button> right,
            std::shared_ptr<Button> a,
            std::shared_ptr<Button> b) :    
        up{std::move(up)}, // BUTTON_PIN_4
        down{std::move(down)},  // BUTTON_PIN_3
        left{std::move(left)},  // BUTTON_PIN_5
        right{std::move(right)},  // BUTTON_PIN_2
        a{std::move(a)},  // BUTTON_PIN_1
        b{std::move(b)}  // BUTTON_PIN_0
    {
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
