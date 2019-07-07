/*Target Class
Class that sets a series of dots in a specific location on the LED strip
*/

class Target {
    public:
        int Loc;
        int Height;
        int Step;
        int Red;
        int Green;
        int Blue;
        long Time;
        bool inTarget;

        //Constructor
        Target(int,int,int,int,int);
};
Target::Target(int loc, int height, int green, int red, int blue)
{
    Loc = loc;
    Height = height;
    Step = Height/6;
    Red = red;
    Green = green;
    Blue = blue;
    Time = 0;
    inTarget = false;
    }
