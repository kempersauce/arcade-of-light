/*Background Class
Class that sets a background color across LED strip
*/

class Background {
    public:
        int Loc;
        int Height;
        int Red;
        int Green;
        int Blue;

        //Constructor
        Background(int,int,int,int,int);
};
Background::Background(int loc, int height, int green, int red, int blue)
{
    Loc = loc;
    Height = height;
    Red = red;
    Green = green;
    Blue = blue;
    }
