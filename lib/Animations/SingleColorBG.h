//Dot Class
//Class that sets a dot in a specific locatio on the LED strip
class SingleColorBG : Animation {
    public:
        //colors (RGB)
        int red;
        int green;
        int blue;
        SingleColorBG(int redColor, int greenColor, int blueColor)
        {
            red = redColor;
            green = greenColor;
            blue = blueColor;
        }
        void setColor(int redColor, int greenColor, int blueColor)
            {
                red = redColor;
                green = greenColor;
                blue = blueColor;

            }
        void draw(Display* display)
        {
            for (int i = 1; i < display->lengthStrips; i++)
                {
                    for (int j = 0; j < display->numStrips; j++) {
                        display->strips[j][i].setRGB(red, green, blue);
                    }
                }
        }


};
