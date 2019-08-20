#pragma once

#include <Dot.h>

class H2HDot : public Dot
{
    public:
        int velocity;

        H2HDot(CRGB startColor, int startX, int startY, int yMaximum)
            : Dot(startColor, startX, startY, startX, yMaximum)
        {
            velocity = 1;
        }

        void vMove()
        {
            move(0, velocity);
        }

        void flip()
        {
            velocity *= -1;
        }
};
