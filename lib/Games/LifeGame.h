#include <LifeAnimation.h>
#include <Game.h>
#include <H2HDisplay.h>

class LifeGame : Game
{
    // Buttons

    // Animations
    LifeAnimation* lifeGrid;

    public:
        LifeGame(Display* display) : Game(display)
        {
            lifeGrid = new LifeAnimation(display->numStrips, display->lengthStrips);
        }

        void setup()
        {
        }

        void loop()
        {
            // Poll buttons

            // Calculate new game state
            lifeGrid->GoOneRound();

            // Draw to display
            lifeGrid->draw(display);
        }
};
