/*
Button Class
creates an object that can read whether or not the button is pressed
*/
class Button {
//Arduino pin button is connected to
int pin;
bool state;
public:
    //Functions
    /**Reads the current state of the button
     * @return - HIGH(1/pressed) or LOW(0/unpressed)
     * */
    int read()
    {
    state = digitalRead(pin);
    }
};
/**
 * Button Constructor
 * @pin number of pin buton is connected to
 */
Button::Button(int pinNumber)
    {
        pinMode(pinNumber, INPUT);
        pin = pinNumber;
    }


/*
Control class
It's all ur buttonz
*/
class Control{
public:
    Map<string,Button> buttons;
};
Control::Control(Map<string,Button> buttonMap){
    buttons = buttonMap;
}
