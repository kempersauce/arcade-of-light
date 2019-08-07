#include <LifeAnimation.h>
#include <Game.h>
#include <H2HDisplay.h>
#include <Button.h>

class LifeGame : Game
{
    // Buttons
    Button randomizeButton;

    // Animations
    LifeAnimation* lifeGrid;

    public:
        LifeGame(Display* display) : Game(display),
            randomizeButton(H2H_BUTTON_PIN_0)
        {
            lifeGrid = new LifeAnimation(display->numStrips, display->lengthStrips);
        }

        void setup()
        {
        }

        void loop()
        {
            // Poll buttons
            randomizeButton.poll();

            // Calculate new game state
            if (randomizeButton.isPressed())
            {
                lifeGrid->randomize();
            }
            else
            {
                lifeGrid->GoOneRound();
            }

            // Draw to display
            lifeGrid->draw(display);
        }
};
