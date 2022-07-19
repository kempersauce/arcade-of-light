#pragma once

#include <button.h>
#include <H2HDot.h>
#include <H2HZone.h>
#include <Explosion.h>
#include <NoiseGenerator.h>
#include <KemperSerialTransmitter.h>
#include <H2HAudio.h>

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
	H2HDot dot;

	// explode when dot hits wall (boom)
	Explosion explosion;

	// Explode the ball out of the gate
	Explosion dropExplosion;

	// nearside team
	H2HZone zoneA;
	static int zoneAStart;
	// static const int zoneAHue = 138; // cyan
	static const int zoneAHue = 120; // green 

	// farside team
	H2HZone zoneB;
	static int zoneBStart;
	// static const int zoneBHue = 0; // red
	static const int zoneBHue = 33; // orange - this is wrong

	int stripIndex; // Which strip is this on?
	int heightMax; // length of this strip

	NoiseGenerator* noiseGenerator; // this is maintained by the game class so we just need to hold onto the reference here

	long stateTimeoutMillis; // state timer used to time a handful of game states
	const static long deadStateTimeoutMinMillis = 1000 * .5; // 1/2 seconds minimum before dropping a new ball
	const static long deadStateTimeoutMaxMillis = 1000 * 5; // 5 seconds max before dropping a new ball

	const static long droppingStateTimeoutMillis = 1000 * 3; // 2 seconds of flashing before ball drop

	const static long totalWinStateTimeoutMillis = 1000 * 3; // loop total win animation for 3 seconds

public:
	H2HStripState stripState;

	// static because they all share the same mid bar
	static int midBar;

	std::shared_ptr<kss::controls::Button> buttonA;
	std::shared_ptr<kss::controls::Button> buttonB;

	H2HGameStrip(int stripIndex, int stripHeight, std::shared_ptr<kss::controls::Button> a, std::shared_ptr<kss::controls::Button> b, NoiseGenerator* noise)
		: Animation(),
		dot(CRGB::White, stripIndex),
		explosion(50),
		dropExplosion(8),
		zoneA(CRGB::Green, stripIndex, 0, 22, false),
		zoneB(CRGB::Yellow, stripIndex, stripHeight - 23, stripHeight - 1, true),
		buttonA{std::move(a)},
		buttonB{std::move(b)}
	{
	    this->stripIndex = stripIndex;
	    heightMax = stripHeight;

		dropExplosion.SaturationFinal = 0; // Gotta keep 'em desaturated
		dropExplosion.saturationPhaseMillis = 150; // hold saturation for a quarter second before fading away
		dropExplosion.brightnessPhaseMillis = 200; // quick little explosion
		dropExplosion.SetFriction(20, 2);
		dropExplosion.explosionMagnitude = 50;

		// Set some physics on the explosion shrapnel so they'll bounce off the ceiling and floor
		for (int i = 0; i < explosion.shrapnel.size(); i++)
		{
			explosion.shrapnel[i].LocationMax = stripHeight;
			explosion.shrapnel[i].BounceFactor = -.8;
		}
		explosion.SetFriction(10, 3);

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
		midBar += 12;

		if (midBar > zoneBStart)
		{
			enterTotalWinAState();
		}
	}

	void enterWinningStateB()
	{
		stripState = H2HStripWinningB;

		explosion.Hue = zoneBHue;
		explosion.ExplodeAt(stripIndex, dot.physics.Location);
		// TODO set this elsewhere once we have an animation for it
		midBar -= 12;

		if (midBar < zoneAStart)
		{
			enterTotalWinBState();
		}
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
		stateTimeoutMillis = millis();
	}

	void enterTotalWinBState()
	{
		stripState = H2HStripTotalWinB;
		stateTimeoutMillis = millis();
	}

	void pollButtons()
	{
	    buttonA->poll();
	    buttonB->poll();
	}

	void checkGameState(H2HAudio* audio)
	{
		switch (stripState)
		{
			case H2HStripPlaying:

				// Did team A just win this one?
				if (dot.physics.Location >= heightMax)
	            {
					audio->playTeamAWinLane();
	                enterWinningStateA();
	            }

				// Did team B just win this one?
	            else if (dot.physics.Location <= 0)
	            {
					audio->playTeamBWinLane();
	                enterWinningStateB();
	            }

				else
				{
					// Team A hits the button
		            if (buttonA->IsDepressing())
		            {
						if (zoneA.checkZone(dot.physics.Location))
						{
							audio->playTeamAHit();
							dot.setVelocity(-1 * (dot.physics.Velocity) + (zoneA.zoneDepth(dot.physics.Location) * 10)); // 20 to 40 px/sec
						}
						else
						{
							audio->playTeamAMiss();
						}
						
		            }

		            // Team B hits the button
		            if (buttonB->IsDepressing())
		            {
						digitalWriteFast(9, HIGH);
 					    delay(1);
    					digitalWriteFast(9, LOW);
						if (zoneB.checkZone(dot.physics.Location))
						{
							audio->playTeamBHit();
							dot.setVelocity(-1 * (dot.physics.Velocity) - (zoneB.zoneDepth(dot.physics.Location) * 10)); // -20 to -40 px/sec
						}
						else
						{
							audio->playTeamBMiss();
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
				// play out residual explosions
				explosion.Move();
				dropExplosion.Move();
				dot.Move();
			break;


			case H2HStripTotalWinB:
				// play out residual explosions
				explosion.Move();
				dropExplosion.Move();
				dot.Move();
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
			break;

			case H2HStripTotalWinA:
		        drawBackgrounds(display);
				//drawZones(display);
				drawMidBar(display);
				explosion.draw(display);
				dropExplosion.draw(display);
            	dot.draw(display);
				drawWinA(display);
			break;

			case H2HStripTotalWinB:
		        drawBackgrounds(display);
				//drawZones(display);
				drawMidBar(display);
				explosion.draw(display);
				dropExplosion.draw(display);
            	dot.draw(display);
				drawWinB(display);
			break;
		}
	}

	void drawBackgrounds(Display* display)
	{
		// Team A background
		drawBackgroundA(display);

		// Team B background
		drawBackgroundB(display);
	}

	void drawBackgroundA(Display* display)
	{
		for (int y = 0; y < min(midBar, display->lengthStrips); y++)
		{
			display->strips[stripIndex][y].setHSV(zoneAHue, 255, noiseGenerator->noise[stripIndex][y]); // blue team
		}
	}

	void drawBackgroundB(Display* display)
	{
		for (int y = max(midBar, 0); y < heightMax; y++)
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
		//display->strips[stripIndex][midBar] = CRGB::White;
	}

	void drawWinA(Display* display)
	{
		CRGB teamAColor;
		teamAColor.setHSV(zoneAHue, 255, 255);
		long timeDiff = (millis() - stateTimeoutMillis) % 2000; // loop thrugh 2 seconds
		const float waveWidth = 10;
		drawBackgroundA(display);
		if (timeDiff < 1000)
		{
			float distance = (float)display->lengthStrips * (float)timeDiff / 1000;
			for (int i = waveWidth / -2; i < waveWidth / 2; i++)
			{
				float presence = (waveWidth / 2 - abs(i)) / (waveWidth / 2);
				display->blendPixel(stripIndex, distance + i, &teamAColor, presence);
			}
		}
	}

	void drawWinB(Display* display)
	{
		CRGB teamBColor;
		teamBColor.setHSV(zoneBHue, 255, 255);
		long timeDiff = (millis() - stateTimeoutMillis) % 2000; // loop thrugh 2 seconds
		const float waveWidth = 10;
		drawBackgroundB(display);
		if (timeDiff < 1000)
		{
			float distance = (float)display->lengthStrips * (float)(1000 - timeDiff) / 1000;
			for (int i = waveWidth / -2; i < waveWidth / 2; i++)
			{
				float presence = (waveWidth / 2 - abs(i)) / (waveWidth / 2);
				display->blendPixel(stripIndex, distance + i, &teamBColor, presence);
			}
		}
	}
};

int H2HGameStrip::midBar;
int H2HGameStrip::zoneAStart;
int H2HGameStrip::zoneBStart;
