#include <Button.h>
#include <PinSetup.h>

class DirPad {
    public:
        int numButtons = 6;
        Button* up;
        Button* down;
        Button* left;
        Button* right;
        Button* a;
        Button* b;

        //Button*[numButtons] buttons;


        DirPad()
        {
            //assign pins to buttons
            up = new Button(BUTTON_PIN_0);
            down = new Button(BUTTON_PIN_1);
            left = new Button(BUTTON_PIN_2);
            right = new Button(BUTTON_PIN_3);
            a = new Button(BUTTON_PIN_4);
            b = new Button(BUTTON_PIN_5);

            //Add button pointers to buttons array
            //buttons = {up,down,left,right,a,b};

        }
        void pollAll(){
            up->poll();
            down->poll();
            left->poll();
            right->poll();
            a->poll();
            b->poll();
        }
};
