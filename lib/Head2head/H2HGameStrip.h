#pragma once

#include <Button.h>
#include <H2HDot.h>
#include <H2HZone.h>
#include <NoiseGenerator.h>

class H2HGameStrip : Animation
{
    H2HDot* dot;

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

    bool teamAWin;
    bool teamBWin;
    static bool teamATotalWin;
    static bool teamBTotalWin;

    H2HGameStrip(int stripIndex, int stripHeight, int buttonAPin, int buttonBPin, NoiseGenerator* noise)
		: Animation(),
		zoneA(CRGB::Green, stripIndex, 0, 22, false),
		zoneB(CRGB::Yellow, stripIndex, stripHeight - 23, stripHeight - 1, true)
    {
        this->stripIndex = stripIndex;
        heightMax = stripHeight;

        buttonA = new Button(buttonAPin);
		zoneAStart = zoneA.yMax;

        buttonB = new Button(buttonBPin);
		zoneBStart = zoneB.yMin;

        dot = new H2HDot(CRGB::White, stripIndex);

        reset();

        noiseGenerator = noise;
    }

    void reset()
    {
        // reset the mid bar
        midBar = heightMax / 2; // dont reset the shared mid when an individual strip wins
        dot->physics.Location = midBar;

        // randomly start in different directions
        if (random16() > UINT16_MAX / 2)
        {
            dot->setVelocity(20);
        }
        else
        {
            dot->setVelocity(-20);
        }

        teamAWin = false;
        teamBWin = false;
        teamATotalWin = false;
        teamBTotalWin = false;
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

        // Check if anybody has won this strip yet
        if (!teamAWin && !teamBWin)
        {
            if (dot->physics.Location >= heightMax)
            {
                //team A wins this strip
                teamAWin = true;

                // set dot to A's side so it can run down to the midbar
                dot->physics.Location = zoneAStart;
                //dot->velocity = 5; // maybe let it just keep its same velocity
            }
            else if (dot->physics.Location <= 0)
            {
                //team B wins this strip
                teamBWin = true;

                // set dot to B's side so it can run down to the midbar
                dot->physics.Location = zoneBStart;
                //dot->velocity = -5; // maybe let it just keep its same velocity
            }
        }

        if (!teamAWin && !teamBWin)
        {

            // Team A hits the button
            if (buttonA->isDepressing())
            {
				if (zoneA.checkZone(dot->physics.Location))
				{
					dot->setVelocity(-1 * (dot->physics.Velocity) + (zoneA.zoneDepth(dot->physics.Location) * 10)); // 20 to 40 px/sec
				}
            }

            // Team B hits the button
            if (buttonB->isDepressing())
            {
				if (zoneB.checkZone(dot->physics.Location))
				{
					dot->setVelocity(-1 * (dot->physics.Velocity) - (zoneB.zoneDepth(dot->physics.Location) * 10)); // -20 to -40 px/sec
				}
            }
        }

        // dot moves either way
        dot->Move();

        // bump the bar after team A is done winning
        if (teamAWin && dot->physics.Location > midBar)
        {
            midBar += 5;
            teamAWin = false;
        }

        // bump the bar after team B is done winning
        if (teamBWin && dot->physics.Location < midBar)
        {
            midBar -= 5;
            teamBWin = false;
        }

        // check if the mid bar is into team A's zone
        if (midBar < zoneAStart)
        {
            teamATotalWin = true;

            // put the dot at the end to draw out the team color
            dot->physics.Location = 0;
            dot->setVelocity(0);
        }

        // check if the mid bar is into team B's zone
        if (midBar > zoneBStart)
        {
            teamBTotalWin = true;

            // put the dot at the end to draw out the team color
            dot->physics.Location = heightMax - 1;
            dot->setVelocity(0);
        }
    }

    void draw(Display* display)
    {
        // Draw backgrounds for both teams up to the dot

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

        // Only draw these if this game is still playing
        if (!teamATotalWin && !teamBTotalWin)
        {
            //// Draw the zones on top of the background
            zoneA.draw(display);
            zoneB.draw(display);

            // Draw the mid bar
            display->strips[stripIndex][midBar] = CRGB::White;

            // Draw the dot last
            dot->draw(display);
        }
    }
};

int H2HGameStrip::midBar;
bool H2HGameStrip::teamATotalWin;
bool H2HGameStrip::teamBTotalWin;
