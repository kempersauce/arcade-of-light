//Dot Class
//Class that sets a dot in a specific locatio on the LED strip
class Dot:Animation {
    public:
        //location values
        int xLoc;
        int yLoc;
        //boundaries of movement Area
        int xMax;
        int yMax;
        //colors (RGB)
        CRGB color;

        //Constructor - COULD BE MORE EFFICIENT
        Dot(CRGB startColor, int startX, int startY, int startZ, int xMaximum, int yMaximum)
            {
                color = startColor;
                xLoc = startX;
                yLoc = startY;
                zLoc = startZ;
                xMax = xMaximum;
                yMax = yMaximum;
            }

        //Methods
        void move(int xMove, int yMove)
        {
            xLoc += xMove;
            yLoc += yMove;
            if(xLoc > xMax){xLoc=xMax;}
            if(yLoc > yMax){yLoc=yMax;}
            if(xLoc < 0){xLoc=0;}
            if(yLoc < 0){yLoc=0;}
        }
        void changeColor(CRGB newColor)
        {
            color = newColor;
        }
        void draw(Display* display)
        {
            display->strips[xLoc][yLoc] = color;
        }
};
