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
	H2HStripDropping,
	H2HStripTotalWinA,
	H2HStripTotalWinB
};

class H2HGameStrip : Animation
{
	H2HStripState stripState;

	H2HDot dot;

	// explode when dot hits wall (boom)
	Explosion explosion;

	// Explode the ball out of the gate
	Explosion dropExplosion;

	// static because they all share the same mid bar
	static int midBar;

	// nearside team
	H2HZone zoneA;
	static int zoneAStart;
	static const int zoneAHue = 130; // cyan

	// farside team
	H2HZone zoneB;
	static int zoneBStart;
	static const int zoneBHue = 215; // magenta

	int stripIndex; // Which strip is this on?
	int heightMax; // length of this strip

	NoiseGenerator* noiseGenerator; // this is maintained by the game class so we just need to hold onto the reference here

	long stateTimeoutMillis; // state timer used to time a handful of game states
	const static long deadStateTimeoutMinMillis = 1000 * .5; // 1/2 seconds minimum before dropping a new ball
	const static long deadStateTimeoutMaxMillis = 1000 * 5; // 5 seconds max before dropping a new ball

	const static long droppingStateTimeoutMillis = 1000 * 2; // 2 seconds of flashing before ball drop

public:
	Button buttonA;
	Button buttonB;

	static bool isTeamAWon()
	{
		return midBar < zoneAStart;
	}

	static bool isTeamBWon()
	{
		return midBar > zoneBStart;
	}

	H2HGameStrip(int stripIndex, int stripHeight, int buttonAPin, int buttonBPin, NoiseGenerator* noise)
		: Animation(),
		dot(CRGB::White, stripIndex),
		explosion(50),
		dropExplosion(25),
		zoneA(CRGB::Green, stripIndex, 0, 22, false),
		zoneB(CRGB::Yellow, stripIndex, stripHeight - 23, stripHeight - 1, true),
		buttonA(buttonAPin),
		buttonB(buttonBPin)
	{
	    this->stripIndex = stripIndex;
	    heightMax = stripHeight;

		dropExplosion.SaturationFinal = 0; // Gotta keep 'em desaturated
		dropExplosion.saturationPhaseMillis = 250; // hold saturation for a quarter second before fading away
		dropExplosion.brightnessPhaseMillis = 250; // quick little explosion

		// Set some physics on the explosion shrapnel so they'll bounce off the ceiling and floor
		for (int i = 0; i < explosion.shrapnel.size(); i++)
		{
			explosion.shrapnel[i].LocationMax = stripHeight;
			explosion.shrapnel[i].BounceFactor = -.8;
		}

		zoneAStart = zoneA.yMax;
		zoneBStart = zoneB.yMin;

	    reset();

	    noiseGenerator = noise;
	}

	void reset()
	{
	    // reset the mid bar
	    midBar = heightMax / 2; // dont reset the shared mid when an individual strip wins

		enterDeadState();
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

		dropExplosion.ExplodeAt(stripIndex, midBar);
	}

	void enterWinningStateA()
	{
		stripState = H2HStripWinningA;

		explosion.Hue = zoneAHue;
		explosion.ExplodeAt(stripIndex, dot.physics.Location);
		// TODO set this elsewhere once we have an animation for it
		midBar += 5;
	}

	void enterWinningStateB()
	{
		stripState = H2HStripWinningB;

		explosion.Hue = zoneBHue;
		explosion.ExplodeAt(stripIndex, dot.physics.Location);
		// TODO set this elsewhere once we have an animation for it
		midBar -= 5;
	}

	void enterDeadState()
	{
		stripState = H2HStripDead;
		// Plan for when to start dropping a new ball
		stateTimeoutMillis = millis() + random(deadStateTimeoutMinMillis, deadStateTimeoutMaxMillis);
	}

	void enterDroppingState()
	{
		stripState = H2HStripDropping;

		// Plan for when the ball actually drops
		stateTimeoutMillis = millis() + droppingStateTimeoutMillis;
	}

	void enterTotalWinAState()
	{
		stripState = H2HStripTotalWinA;
	}

	void enterTotalWinBState()
	{
		stripState = H2HStripTotalWinB;
	}

	void pollButtons()
	{
	    buttonA.poll();
	    buttonB.poll();
	}

	void checkGameState()
	{
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
		            if (buttonA.isDepressing())
		            {
						if (zoneA.checkZone(dot.physics.Location))
						{
							dot.setVelocity(-1 * (dot.physics.Velocity) + (zoneA.zoneDepth(dot.physics.Location) * 10)); // 20 to 40 px/sec
						}
		            }

		            // Team B hits the button
		            if (buttonB.isDepressing())
		            {
						if (zoneB.checkZone(dot.physics.Location))
						{
							dot.setVelocity(-1 * (dot.physics.Velocity) - (zoneB.zoneDepth(dot.physics.Location) * 10)); // -20 to -40 px/sec
						}
		            }

			        // dot moves either way
			        dot.Move();

					// play out the residual drop explosion
					dropExplosion.Move();
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
				if (millis() > stateTimeoutMillis)
				{
					enterDroppingState();
				}
			break;

			case H2HStripDropping:
				if (millis() <= stateTimeoutMillis)
				{
					if (dropExplosion.IsBurnedOut())
					{
						dropExplosion.ExplodeAt(stripIndex, midBar);
					}
					dropExplosion.Move();
				}
				else
				{
					enterPlayingState();
				}
			break;

			case H2HStripTotalWinA:
			case H2HStripTotalWinB:
				// play out residual explosions
				explosion.Move();
				dropExplosion.Move();
			break;
		}
	}

	void draw(Display* display)
	{
		switch (stripState)
		{
			case H2HStripPlaying:
		        drawBackgrounds(display);
				drawZones(display);
				drawMidBar(display);
				//explosion.draw(display);
				dropExplosion.draw(display); // play out the last residual explosion
	            dot.draw(display);
			break;

			case H2HStripWinningA:
			case H2HStripWinningB:
		        drawBackgrounds(display);
				drawZones(display);
				drawMidBar(display);
				explosion.draw(display);
				//dropExplosion.draw(display);
	            //dot.draw(display);
			break;

			case H2HStripDead:
		        drawBackgrounds(display);
				drawZones(display);
				drawMidBar(display);
				//explosion.draw(display);
				//dropExplosion.draw(display);
	            //dot.draw(display);
			break;

			case H2HStripDropping:
		        drawBackgrounds(display);
				drawZones(display);
				drawMidBar(display);
				//explosion.draw(display);
				dropExplosion.draw(display);
            	//dot.draw(display);
				display->strips[stripIndex][midBar].setHSV(85, (millis() - dropExplosion.birthTimeMillis) % 256, 255); // green flash
			break;

			case H2HStripTotalWinA:
		        drawBackgrounds(display);
				//drawZones(display);
				drawMidBar(display);
				explosion.draw(display);
				dropExplosion.draw(display);
            	dot.draw(display);
			break;

			case H2HStripTotalWinB:
		        drawBackgrounds(display);
				//drawZones(display);
				drawMidBar(display);
				explosion.draw(display);
				dropExplosion.draw(display);
            	dot.draw(display);
			break;
		}
	}

	void drawBackgrounds(Display* display)
	{
		// Team A background
		for (int y = 0; y < midBar; y++)
		{
			display->strips[stripIndex][y].setHSV(zoneAHue, 255, noiseGenerator->noise[stripIndex][y]); // blue team
		}

		// Team B background
		for (int y = midBar; y < heightMax; y++)
		{
			display->strips[stripIndex][y].setHSV(zoneBHue, 255, noiseGenerator->noise[stripIndex][y]); // red team
		}
	}

	void drawZones(Display* display)
	{
		zoneA.draw(display);
		zoneB.draw(display);
	}

	void drawMidBar(Display* display)
	{
		display->strips[stripIndex][midBar] = CRGB::White;
	}
};

int H2HGameStrip::midBar;
int H2HGameStrip::zoneAStart;
int H2HGameStrip::zoneBStart;
