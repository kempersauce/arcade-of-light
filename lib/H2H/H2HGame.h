#include <H2HAnimation.h>

class H2HGame
{
    public:
        H2HAnimation* background;
        H2HDisplay* display;
        H2HGame(H2HDisplay* gameDisplay)
            : display(gameDisplay)
        {
        }

        virtual void setup();
        virtual void loop();
};
