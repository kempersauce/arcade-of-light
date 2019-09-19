#pragma once

#include <Button.h>
#include <H2HDot.h>
#include <H2HZone.h>
#include <NoiseGenerator.h>

class H2HGameStrip : Animation
{
    H2HDot* dot;

    // nearside team
    H2HZone* zoneA1;
    H2HZone* zoneA2;
    H2HZone* zoneA3;
    int zoneAStart;

    // farside team
    H2HZone* zoneB1;
    H2HZone* zoneB2;
    H2HZone* zoneB3;
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
    {
        this->stripIndex = stripIndex;
        heightMax = stripHeight;

        buttonA = new Button(buttonAPin);
        zoneA1 = new H2HZone(CRGB::Cyan, stripIndex, 15, 25);
        zoneA2 = new H2HZone(CRGB::Blue, stripIndex, 8, 15);
        zoneA3 = new H2HZone(CRGB::Green, stripIndex, 4, 8);
        zoneAStart = zoneA1->yMax;

        buttonB = new Button(buttonBPin);
        zoneB1 = new H2HZone(CRGB::Yellow, stripIndex, stripHeight - 25, stripHeight - 15);
        zoneB2 = new H2HZone(CRGB::Red, stripIndex, stripHeight - 15, stripHeight - 8);
        zoneB3 = new H2HZone(CRGB::Orange, stripIndex, stripHeight - 8, stripHeight - 4);
        zoneBStart = zoneB1->yMin;

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
                if (zoneA3->checkZone(dot->yLoc))
                {
                    // team A hit the ball back hard
                    dot->velocity = 3;
                }
                else if (zoneA2->checkZone(dot->yLoc))
                {
                    // team A hit the ball back medium
                    dot->velocity = 2;
                }
                else if (zoneA1->checkZone(dot->yLoc))
                {
                    // team A hit the ball back soft
                    dot->velocity = 1;
                }
            }

            // Team B hits the button
            if (buttonB->isDepressing())
            {
                if (zoneB3->checkZone(dot->yLoc))
                {
                    // team B hit the ball back hard
                    dot->velocity = -3;
                }
                else if (zoneB2->checkZone(dot->yLoc))
                {
                    // team B hit the ball back medium
                    dot->velocity = -2;
                }
                else if (zoneB1->checkZone(dot->yLoc))
                {
                    // team B hit the ball back soft
                    dot->velocity = -1;
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
            //zoneA1->draw(display);
            //zoneA2->draw(display);
            //zoneA3->draw(display);

            //zoneB1->draw(display);
            //zoneB2->draw(display);
            //zoneB3->draw(display);

            // JK lets just do this ourselves for now so its not broken accross zones
            int aStart = zoneA3->yMin;
            int bStart = zoneB1->yMin;
            int range = zoneA1->yMax - aStart;

            // I think this is okay, as long as we're not using new, they should automatically fall off the stack and create no memory leaks
            CRGB cyan = CRGB::Cyan;
            CRGB yellow = CRGB::Yellow;

            for (int i = 0; i < range; i++)
            {
                // How far down the color blend we are
                float blendFactor = (float)i / (float)range;

                // fade A from green (hard hit side) to cyan (light hit side)
                display->strips[stripIndex][aStart + i] = CRGB::Green;
                blendPixel(&display->strips[stripIndex][aStart + i], &cyan, blendFactor);

                // fade B from orange (light hit side) to yellow (hard hit side)
                display->strips[stripIndex][bStart + i] = CRGB::Orange;
                blendPixel(&display->strips[stripIndex][bStart + i], &yellow, blendFactor);
            }

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
