#pragma once

#include <Button.h>
#include <H2HDot.h>
#include <H2HZone.h>
#include <NoiseGenerator.h>

class H2HGameStrip
{
    H2HDot* dot;

    // nearside team
    Button* buttonA;
    H2HZone* zoneA1;
    H2HZone* zoneA2;
    H2HZone* zoneA3;

    // farside team
    Button* buttonB;
    H2HZone* zoneB1;
    H2HZone* zoneB2;
    H2HZone* zoneB3;

    int stripIndex; // Which strip is this on?
    int heightMax; // length of this strip

    NoiseGenerator* noiseGenerator; // this is maintained by the game class so we just need to hold onto the reference here

public:
    bool teamAWin = false;
    bool teamBWin = false;

    H2HGameStrip(int stripIndex, int stripHeight, int buttonAPin, int buttonBPin, NoiseGenerator* noise)
    {
        this->stripIndex = stripIndex;
        this->heightMax = stripHeight;

        this->buttonA = new Button(buttonAPin);
        this->zoneA1 = new H2HZone(CRGB::Cyan, stripIndex, 4, 24);
        this->zoneA2 = new H2HZone(CRGB::Blue, stripIndex, 8, 20);
        this->zoneA3 = new H2HZone(CRGB::Green, stripIndex, 12, 16);

        this->buttonB = new Button(buttonBPin);
        this->zoneB1 = new H2HZone(CRGB::Yellow, stripIndex, stripHeight - 24, stripHeight - 4);
        this->zoneB2 = new H2HZone(CRGB::Red, stripIndex, stripHeight - 20, stripHeight - 8);
        this->zoneB3 = new H2HZone(CRGB::Orange, stripIndex, stripHeight - 16, stripHeight - 12);

        this->dot = new H2HDot(CRGB::White, stripIndex, stripHeight / 2, stripHeight);

        reset();

        noiseGenerator = noise;
    }

    void reset()
    {
        // randomly start in different directions
        if (random8() > 127)
        {
            dot->velocity = 1;
        }
        else
        {
            dot->velocity = -1;
        }

        dot->yLoc = heightMax / 2;

        teamAWin = false;
        teamBWin = false;
    }

    void pollButtons()
    {
        buttonA->poll();
        buttonB->poll();
    }

    void checkGameState()
    {
        // Check if anybody has won this strip yet
        if (!teamAWin && !teamBWin)
        {
            if (dot->yLoc >= heightMax)
            {
                //team A wins this strip
                teamAWin = true;
            }
            else if (dot->yLoc <= 0)
            {
                //team B wins this strip
                teamBWin = true;
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

            dot->vMove();
        }
    }

    void draw(Display* display)
    {
        // Draw backgrounds for both teams up to the dot

        // Team A background
        for (int y = 0; y < dot->yLoc; y++)
        {
            display->strips[stripIndex][y] = CRGB(0, 0, noiseGenerator->noise[stripIndex][y]); // blue team
        }

        // Team B background
        for (int y = dot->yLoc + 1; y < heightMax; y++)
        {
            display->strips[stripIndex][y] = CRGB(noiseGenerator->noise[stripIndex][y], 0, 0); // red team
        }

        // Only draw these if this strip is still playing
        if (!teamAWin && !teamBWin)
        {
            // Draw the zones on top of the background
            zoneA1->draw(display);
            zoneA2->draw(display);
            zoneA3->draw(display);

            zoneB1->draw(display);
            zoneB2->draw(display);
            zoneB3->draw(display);

            // Draw the dot last
            dot->draw(display);
        }
    }
};
