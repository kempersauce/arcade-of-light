#include <Animation.h>

class FinishLine : Animation
{
    public:
        int Loc;
        int Stripes[5][4] = {
        0,1,0,1,0
        1,0,1,0,1
        0,1,0,1,0
        1,0,1,0,1
        };

        //Constructor
        Target(int loc)
            : Animation()
        {
            Loc = loc;
        }

        void draw(Display* display)
        {


            }
        }

};
