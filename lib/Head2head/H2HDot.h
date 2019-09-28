#pragma once

#include <PhysicsInfo.h>
#include <FastLED.h>

class H2HDot : public Animation
{
    public:
        PhysicsInfo physics;
		CRGB color;

        H2HDot(CRGB startColor, int stripIndex)
            : Animation(),
			physics()
        {
			color = startColor;
            physics.xLocation = stripIndex;
        }

        void Move()
        {
			physics.Move();
        }

		void setVelocity(float velocity)
		{
			physics.Velocity = (int)velocity;
		}

        void draw(Display* display)
        {
			// Don't draw outside the display boundaries
			if (physics.HasHitEdge == false)
			{
				//float dither = physics.Location % 1;
            	display->strips[(int)physics.xLocation][(int)physics.Location] = color;
			}
        }
};
