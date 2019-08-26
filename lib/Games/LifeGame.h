#include <LifeAnimation.h>
#include <Game.h>
#include <Button.h>

class LifeGame : Game
{
    // Buttons
    Button randomizeButton1;
    Button randomizeButton2;

    Button gliderButton1;
    Button gliderButton2;

    // Animations
    LifeAnimation* lifeGrid;

    public:
        LifeGame(Display* display) : Game(display),
            randomizeButton1(H2H_BUTTON_PIN_0),
            randomizeButton2(H2H_BUTTON_PIN_8),
            gliderButton1(H2H_BUTTON_PIN_7),
            gliderButton2(H2H_BUTTON_PIN_15)
        {
            lifeGrid = new LifeAnimation(display->numStrips, display->lengthStrips);
        }

        void setup()
        {
            // start off randomized
            lifeGrid->randomize();
        }

        void loop()
        {
            delay(30); // slow it down a bit

            // Poll buttons
            randomizeButton1.poll();
            randomizeButton2.poll();
            gliderButton1.poll();
            gliderButton2.poll();

            // Calculate new game state
            if (randomizeButton1.isPressed() || randomizeButton2.isPressed())
            {
                lifeGrid->randomize();
            }
            else
            {
                lifeGrid->GoOneRound();
            }

            if (gliderButton1.isDepressing())
            {
                lifeGrid->setCellState(2, 1, true);
                lifeGrid->setCellState(2, 2, true);
                lifeGrid->setCellState(2, 3, true);
                lifeGrid->setCellState(3, 3, true);
                lifeGrid->setCellState(4, 2, true);
            }

            if (gliderButton2.isDepressing())
            {
                lifeGrid->setCellState(2, display->lengthStrips - 2, true);
                lifeGrid->setCellState(2, display->lengthStrips - 3, true);
                lifeGrid->setCellState(2, display->lengthStrips - 4, true);
                lifeGrid->setCellState(3, display->lengthStrips - 4, true);
                lifeGrid->setCellState(4, display->lengthStrips - 3, true);
            }

            // Draw to display
            lifeGrid->draw(display);
        }
};
