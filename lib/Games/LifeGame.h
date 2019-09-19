#pragma once

#include <LifeAnimation.h>
#include <Game.h>

class LifeGame : Game
{
    // Animations
    LifeAnimation* lifeGrid;

public:
    LifeGame(Display* display) : Game(display)
    {
        lifeGrid = new LifeAnimation(display->numStrips, display->lengthStrips);
    }

    void setup()
    {
        // start off randomized
        lifeGrid->randomize();
    }

    virtual void loop()
    {
        // Calculate next round
        lifeGrid->GoOneRound();
        
        // Draw to display
        lifeGrid->draw(display);
    }
};
