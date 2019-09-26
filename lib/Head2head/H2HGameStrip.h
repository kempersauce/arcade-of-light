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
		zoneA(CRGB::Green, stripIndex, 0, 22),
		zoneB(CRGB::Yellow, stripIndex, stripHeight - 23, stripHeight - 1)
    {
        this->stripIndex = stripIndex;
        heightMax = stripHeight;

        buttonA = new Button(buttonAPin);
		zoneAStart = zoneA.yMax;

        buttonB = new Button(buttonBPin);
		zoneBStart = zoneB.yMin;

        dot = new H2HDot(CRGB::White, stripIndex, stripHeight / 2, stripHeight);

        reset();

        noiseGenerator = noise;
    }

    void reset()
    {
        // reset the mid bar
        midBar = heightMax / 2; // dont reset the shared mid when an individual strip wins
        dot->yLoc = midBar;

        // randomly start in different directions
        if (random8() > 127)
        {
            dot->velocity = 1;
        }
        else
        {
            dot->velocity = -1;
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
            if (dot->yLoc >= heightMax)
            {
                //team A wins this strip
                teamAWin = true;

                // set dot to A's side so it can run down to the midbar
                dot->yLoc = zoneAStart;
                //dot->velocity = 5; // maybe let it just keep its same velocity
            }
            else if (dot->yLoc <= 0)
            {
                //team B wins this strip
                teamBWin = true;

                // set dot to B's side so it can run down to the midbar
                dot->yLoc = zoneBStart;
                //dot->velocity = -5; // maybe let it just keep its same velocity
            }
        }

        if (!teamAWin && !teamBWin)
        {
            // Team A hits the button
            if (buttonA->isDepressing())
            {
				if (zoneA.checkZone(dot->yLoc))
				{
					dot->velocity = zoneA.zoneDepth(dot->yLoc) * 2 + 1; // 1.0 to 3.0 px/frame
				}
            }

            // Team B hits the button
            if (buttonB->isDepressing())
            {
				if (zoneB.checkZone(dot->yLoc))
				{
					dot->velocity = -1 * (zoneB.zoneDepth(dot->yLoc) * 2 + 1); // -1.0 to -3.0 px/frame
				}
            }
        }

        // dot moves either way
        dot->vMove();

        // bump the bar after team A is done winning
        if (teamAWin && dot->yLoc > midBar)
        {
            midBar += 5;
            teamAWin = false;
        }

        // bump the bar after team B is done winning
        if (teamBWin && dot->yLoc < midBar)
        {
            midBar -= 5;
            teamBWin = false;
        }

        // check if the mid bar is into team A's zone
        if (midBar < zoneAStart)
        {
            teamATotalWin = true;

            // put the dot at the end to draw out the team color
            dot->yLoc = 0;
            dot->velocity = 0;
        }

        // check if the mid bar is into team B's zone
        if (midBar > zoneBStart)
        {
            teamBTotalWin = true;

            // put the dot at the end to draw out the team color
            dot->yLoc = heightMax - 1;
            dot->velocity = 0;
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
