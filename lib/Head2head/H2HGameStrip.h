#pragma once

#include <Button.h>
#include <H2HDot.h>
#include <H2HZone.h>
#include <Explosion.h>
#include <NoiseGenerator.h>

enum H2HStripState
{
	H2HStripPlaying,
	H2HStripWinningA,
	H2HStripWinningB,
	H2HStripDead,
	H2HStripDropping
};

class H2HGameStrip : Animation
{
	H2HStripState stripState;

    H2HDot dot;

	// explode when dot hits wall (boom)
    Explosion explosion;

    // nearside team
    H2HZone zoneA;
    int zoneAStart;

    // farside team
    H2HZone zoneB;
    int zoneBStart;

    int stripIndex; // Which strip is this on?
    int heightMax; // length of this strip

    // static because they all share the same mid bar
    static int midBar;

    NoiseGenerator* noiseGenerator; // this is maintained by the game class so we just need to hold onto the reference here

public:
    Button* buttonA;
    Button* buttonB;

    static bool teamATotalWin;
    static bool teamBTotalWin;

    H2HGameStrip(int stripIndex, int stripHeight, int buttonAPin, int buttonBPin, NoiseGenerator* noise)
		: Animation(),
		dot(CRGB::White, stripIndex),
		explosion(),
		zoneA(CRGB::Green, stripIndex, 0, 22, false),
		zoneB(CRGB::Yellow, stripIndex, stripHeight - 23, stripHeight - 1, true)
    {
        this->stripIndex = stripIndex;
        heightMax = stripHeight;

		explosion.stripIndex = stripIndex;

		// Set some physics on the explosion shrapnel so they'll bounce off the ceiling and floor
		for (int i = 0; i < explosion.shrapnelCount; i++)
		{
			explosion.shrapnel[i].LocationMax = stripHeight;
			explosion.shrapnel[i].BounceFactor = -.8;
		}

        buttonA = new Button(buttonAPin);
		zoneAStart = zoneA.yMax;

        buttonB = new Button(buttonBPin);
		zoneBStart = zoneB.yMin;

        reset();

        noiseGenerator = noise;
    }

    void reset()
    {
        // reset the mid bar
        midBar = heightMax / 2; // dont reset the shared mid when an individual strip wins

		enterDeadState();

        teamATotalWin = false;
        teamBTotalWin = false;
    }

	void enterPlayingState()
	{
		stripState = H2HStripPlaying;
		dot.physics.Reset();
		dot.physics.Location = midBar;

		// randomly start in different directions
		if (random16() > UINT16_MAX / 2)
		{
			dot.setVelocity(20);
		}
		else
		{
			dot.setVelocity(-20);
		}
	}

	void enterWinningStateA()
	{
		stripState = H2HStripWinningA;

		explosion.Hue = 160;
		explosion.ExplodeAt(dot.physics.Location);
		// TODO set this elsewhere once we have an animation for it
		midBar += 5;
	}

	void enterWinningStateB()
	{
		stripState = H2HStripWinningB;

		explosion.Hue = 0;
		explosion.ExplodeAt(dot.physics.Location);
		// TODO set this elsewhere once we have an animation for it
		midBar -= 5;
	}

	void enterDeadState()
	{
		stripState = H2HStripDead;

		// check if the mid bar is into team A's zone
		if (midBar < zoneAStart)
		{
			teamATotalWin = true;
		}

        // check if the mid bar is into team B's zone
        else if (midBar > zoneBStart)
        {
            teamBTotalWin = true;
		}
	}

	void enterDroppingState()
	{
		stripState = H2HStripDropping;
	}

    void pollButtons()
    {
        buttonA->poll();
        buttonB->poll();
    }

    void checkGameState()
    {
        // let the game hang on total win
        if (teamATotalWin || teamBTotalWin)
        {
            return;
        }

		switch (stripState)
		{
			case H2HStripPlaying:

				// Did team A just win this one?
				if (dot.physics.Location >= heightMax)
	            {
	                enterWinningStateA();
	            }

				// Did team B just win this one?
	            else if (dot.physics.Location <= 0)
	            {
	                enterWinningStateB();
	            }

				else
				{
					// Team A hits the button
		            if (buttonA->isDepressing())
		            {
						if (zoneA.checkZone(dot.physics.Location))
						{
							dot.setVelocity(-1 * (dot.physics.Velocity) + (zoneA.zoneDepth(dot.physics.Location) * 10)); // 20 to 40 px/sec
						}
		            }

		            // Team B hits the button
		            if (buttonB->isDepressing())
		            {
						if (zoneB.checkZone(dot.physics.Location))
						{
							dot.setVelocity(-1 * (dot.physics.Velocity) - (zoneB.zoneDepth(dot.physics.Location) * 10)); // -20 to -40 px/sec
						}
		            }

			        // dot moves either way
			        dot.Move();
				}
			break;

			case H2HStripWinningA:
				explosion.Move();
				if (explosion.IsBurnedOut())
				{
					// For now immediately go into dead state
					enterDeadState();
				}
			break;

			case H2HStripWinningB:
				explosion.Move();
				if (explosion.IsBurnedOut())
				{
					// For now immediately go into dead state
					enterDeadState();
				}
			break;

			case H2HStripDead:
				// For now immediately go into Dropping state
				enterDroppingState();
			break;

			case H2HStripDropping:
				// For now we go straight to playing
				enterPlayingState();
			break;
		}
    }

    void draw(Display* display)
    {
		switch (stripState)
		{
			case H2HStripPlaying:
		        // Team A background
		        for (int y = 0; y < midBar; y++)
		        {
		            display->strips[stripIndex][y] = CRGB(0, 0, noiseGenerator->noise[stripIndex][y]); // blue team
		        }

		        // Team B background
		        for (int y = midBar; y < heightMax; y++)
		        {
		            display->strips[stripIndex][y] = CRGB(noiseGenerator->noise[stripIndex][y], 0, 0); // red team
		        }

	            // Draw the zones on top of the background
	            zoneA.draw(display);
	            zoneB.draw(display);

	            // Draw the mid bar
	            display->strips[stripIndex][midBar] = CRGB::White;

	            // Draw the dot last
	            dot.draw(display);
			break;

			case H2HStripWinningA:
		        // Team A background
		        for (int y = 0; y < midBar; y++)
		        {
		            display->strips[stripIndex][y] = CRGB(0, 0, noiseGenerator->noise[stripIndex][y]); // blue team
		        }

		        // Team B background
		        for (int y = midBar; y < heightMax; y++)
		        {
		            display->strips[stripIndex][y] = CRGB(noiseGenerator->noise[stripIndex][y], 0, 0); // red team
		        }

	            // Draw the zones on top of the background
	            zoneA.draw(display);
	            zoneB.draw(display);

	            // Draw the mid bar
	            display->strips[stripIndex][midBar] = CRGB::White;

				explosion.draw(display);

	            // Draw the dot last
	            //dot.draw(display);

			break;

			case H2HStripWinningB:
		        // Team A background
		        for (int y = 0; y < midBar; y++)
		        {
		            display->strips[stripIndex][y] = CRGB(0, 0, noiseGenerator->noise[stripIndex][y]); // blue team
		        }

		        // Team B background
		        for (int y = midBar; y < heightMax; y++)
		        {
		            display->strips[stripIndex][y] = CRGB(noiseGenerator->noise[stripIndex][y], 0, 0); // red team
		        }

	            // Draw the zones on top of the background
	            zoneA.draw(display);
	            zoneB.draw(display);

	            // Draw the mid bar
	            display->strips[stripIndex][midBar] = CRGB::White;

				explosion.draw(display);

	            // Draw the dot last
	            //dot.draw(display);

			break;

			case H2HStripDead:
		        // Team A background
		        for (int y = 0; y < midBar; y++)
		        {
		            display->strips[stripIndex][y].setRGB(0, 0, noiseGenerator->noise[stripIndex][y]); // blue team
		        }

		        // Team B background
		        for (int y = midBar; y < heightMax; y++)
		        {
		            display->strips[stripIndex][y].setRGB(noiseGenerator->noise[stripIndex][y], 0, 0); // red team
		        }

	            // Draw the zones on top of the background
	            zoneA.draw(display);
	            zoneB.draw(display);

	            // Draw the mid bar
	            display->strips[stripIndex][midBar] = CRGB::White;
			break;

			case H2HStripDropping:
		        // Team A background
		        for (int y = 0; y < midBar; y++)
		        {
		            display->strips[stripIndex][y].setRGB(0, 0, noiseGenerator->noise[stripIndex][y]); // blue team
		        }

		        // Team B background
		        for (int y = midBar; y < heightMax; y++)
		        {
		            display->strips[stripIndex][y].setRGB(noiseGenerator->noise[stripIndex][y], 0, 0); // red team
		        }

	            // Draw the zones on top of the background
	            zoneA.draw(display);
	            zoneB.draw(display);

				display->strips[stripIndex][midBar].setRGB(0, 255, 0); // green flash
			break;
		}
    }
};

int H2HGameStrip::midBar;
bool H2HGameStrip::teamATotalWin;
bool H2HGameStrip::teamBTotalWin;
