/*
Game class
Where the magic happens
*/
#include <Animation.h>
#include <Control.h>
#include <Display.h>

class Game{
    public:
        Animation background;
        Display* display;
        Game(Display* gameDisplay)
            : display(gameDisplay)
        {
        }

        abstract void setup();
        abstract void loop();
};
