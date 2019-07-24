//Dot Class
//Class that sets a dot in a specific locatio on the LED strip
#include <Animation.h>
#define MASS 2
#define GRAVITY 15
#define THRUST 200

class Dot::Animation {
    public:
        //location values
        int xLoc;
        int yLoc;
        //boundaries of movement Area
        int xMax;
        int yMax;
        //colors (RGB)
        int Red;
        int Green;
        int Blue;

    //Methods

    void Move(int xMove, int yMove)
    {
        xLoc += xMove;
        yLoc += yMove;
    }

    void Flip()
    {
        Velocity = Velocity * -1;
        if(Velocity<6){
            Velocity = Velocity * 1.1;
        }
    }

    //Constructor
    Dot(int, int, int, int);
};
/**
 * Dot Constructor
 * @param loc - location on LED strip
 * @param red - red value (0-255)
 * @param green - green value (0-255)
 * @param blue - blue value (0-255)
 * */
Dot::Dot(int loc, int green, int red, int blue)
{
    Loc = loc;
    Height = 1; //change this later to be adjustable
    Red = red;
    Green = green;
    Blue = blue;
    Velocity = 0;
    InitialVelocity = 1;
}
