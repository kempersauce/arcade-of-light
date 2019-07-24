#include <Button.h>
#include <Constants.h>

class DirPad {
    public:
        const int numButtons;
        Button* up;
        Button* down;
        Button* left;
        Button* right;
        Button* a;
        Button* b;

        Button** buttons;


        DirPad()
        {
            //assign pins to buttons
            up = new Button(BUTTON_PIN_0)
            down = new Button(BUTTON_PIN_1)
            left = new Button(BUTTON_PIN_2)
            right = new Button(BUTTON_PIN_3)
            a = new Button(BUTTON_PIN_4)
            b = new Button(BUTTON_PIN_5)

            //Add button pointers to buttons array
            buttons = {up,down,left,right,a,b};

        }
        ReadAll(){
            for(int i=0; i<buttons.length; i++){
                buttons[i]->Read()
            }
        }
}
