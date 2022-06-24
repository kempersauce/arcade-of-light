#pragma once

#include <Button.h>
#include <Constants.h>

class DirPadMatrix
{
public:
    Button** teamA;
    Button** teamB;
    Button** teamC;
    Button** teamD;

    Button up;
    Button down;
    Button left;
    Button right;
    Button a;
    Button b;

    // DirPad() :
		// up(BUTTON_PIN_5),
		// down(BUTTON_PIN_2),
		// left(BUTTON_PIN_4),
		// right(BUTTON_PIN_3),
		// a(BUTTON_PIN_0),
		// b(BUTTON_PIN_1)
    // {
    // }

        DirPad() :
		up(BUTTON_PIN_0),
		down(BUTTON_PIN_1),
		left(BUTTON_PIN_2),
		right(BUTTON_PIN_3),
		a(BUTTON_PIN_4),
		b(BUTTON_PIN_5)
    {
    }

//TODO Create controller array
//rows= number of controllers
//columns = number of inputs
// head to head has more inputs that pins so will need to poll controller 1 & 2 for 1 player & controller 3&4 for 2 player


    void pollAll()
	{
    //set contoller output we want to read to LOW, ex. read first controller
   for (int controller=0; controller < numControllers; controller++){
    digitalWrite(controller, LOW);
    up.poll();
    down.poll();
    left.poll();
    right.poll();
    a.poll();
    b.poll();
    digitalWrite(controller, HIGH);
}
   }





};
