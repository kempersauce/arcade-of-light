#include <Game.h>
#include <Constants.h>
#include <Button.h>
#include <H2HDisplay.h>
#include <H2HControls.h>
#include <SingleColorBG.h>
#include <H2HDot.h>
#include <H2HZone.h>

class H2HGameStrip
{
    H2HDot* dot;

    // nearside team
    Button* buttonA;
    H2HZone* zoneA;
    CRGB* colorA;

    // farside team
    Button* buttonB;
    H2HZone* zoneB;
    CRGB* colorB;

    int stripIndex; // Which strip is this on?
    int heightMax; // length of this strip

public:
    bool teamAWin = false;
    bool teamBWin = false;

    H2HGameStrip(int stripIndex, int stripHeight, int buttonAPin, CRGB colorA, int buttonBPin, CRGB colorB)
    {
        this->stripIndex = stripIndex;
        this->heightMax = stripHeight;

        this->buttonA = new Button(buttonAPin);
        this->zoneA = new H2HZone(CRGB::Blue, stripIndex, 10, 20);
        this->colorA = &colorA;

        this->buttonB = new Button(buttonBPin);
        this->zoneB = new H2HZone(CRGB::Red, stripIndex, stripHeight - 20, stripHeight - 10);
        this->colorB = &colorB;

        this->dot = new H2HDot(CRGB::White, stripIndex, stripHeight / 2, stripHeight);
    }

    void pollButtons()
    {
        buttonA->poll();
        buttonB->poll();
    }

    void checkGameState()
    {
        // nothing to do here if this strip is already won
        if (!teamAWin && !teamBWin)
        {
            int y = dot->yLoc;
            if (y >= heightMax)
            {
                //team A wins this strip
                teamAWin = true;
            }
            else if (y <= 0)
            {
                //team B wins this strip
                teamBWin = true;
            }
            else if (buttonA->isDepressing() && zoneA->checkZone(dot->yLoc))
            {
                // team A hit the ball back
                dot->velocity = abs(dot->velocity);
            }
            else if (buttonB->isDepressing() && zoneB->checkZone(dot->yLoc))
            {
                // team B hit the ball back
                dot->velocity = abs(dot->velocity) * -1;
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
            display->strips[stripIndex][y] = *colorA;
        }

        // Team B background
        for (int y = dot->yLoc + 1; y < heightMax; y++)
        {
            display->strips[stripIndex][y] = *colorB;
        }

        // Only draw these if this strip is still playing
        if (!teamAWin && !teamBWin)
        {
            // Draw the zones on top of the background
            zoneA->draw(display);
            zoneB->draw(display);

            // Draw the dot last
            dot->draw(display);
        }
    }
};


class Head2Head : Game
{
    public:
        H2HGameStrip** gameStrips; // one for each strip

        Head2Head(Display* gameDisplay)
            : Game(gameDisplay)
        {
            gameStrips = new H2HGameStrip*[gameDisplay->numStrips];

            // Do this one at a time so we can feed it pin numbers and button colors
            gameStrips[0] = new H2HGameStrip(0, gameDisplay->lengthStrips, H2H_BUTTON_PIN_7, CRGB::Green, H2H_BUTTON_PIN_8, CRGB::Yellow);
            gameStrips[1] = new H2HGameStrip(1, gameDisplay->lengthStrips, H2H_BUTTON_PIN_6, CRGB::Blue, H2H_BUTTON_PIN_9, CRGB::Red);
            gameStrips[2] = new H2HGameStrip(2, gameDisplay->lengthStrips, H2H_BUTTON_PIN_5, CRGB::Green, H2H_BUTTON_PIN_10, CRGB::Yellow);
            gameStrips[3] = new H2HGameStrip(3, gameDisplay->lengthStrips, H2H_BUTTON_PIN_4, CRGB::Blue, H2H_BUTTON_PIN_11, CRGB::Red);
            gameStrips[4] = new H2HGameStrip(4, gameDisplay->lengthStrips, H2H_BUTTON_PIN_3, CRGB::Blue, H2H_BUTTON_PIN_12, CRGB::Red);
            gameStrips[5] = new H2HGameStrip(5, gameDisplay->lengthStrips, H2H_BUTTON_PIN_2, CRGB::Green, H2H_BUTTON_PIN_13, CRGB::Yellow);
            gameStrips[6] = new H2HGameStrip(6, gameDisplay->lengthStrips, H2H_BUTTON_PIN_1, CRGB::Blue, H2H_BUTTON_PIN_14, CRGB::Red);
            gameStrips[7] = new H2HGameStrip(7, gameDisplay->lengthStrips, H2H_BUTTON_PIN_0, CRGB::Green, H2H_BUTTON_PIN_15, CRGB::Yellow);
        }

        void setup()
        {
            FastLED.setBrightness(50);
        }

        void loop()
        {
            // Since these dont actually overlap, we can do them in serial
            for (int i = 0; i < 8; i++)
            {
                gameStrips[i]->pollButtons();
                gameStrips[i]->checkGameState();
                gameStrips[i]->draw(display);
            }
        }
};
