/*
Animation class
Make the pretty lights
Make the lights pretty
*/

#pragma once

#include <Display.h>

class Animation
{
    private:
        int zLoc; // TODO do we need this? I'm making it private for now until somebody cries about it

    public:
        virtual void draw(Display* display);
};
