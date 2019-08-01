#include <Button.h>
#include <Constants.h>

class H2HControls {
    public:
        const int numButtons;
        Button*[16] buttons;
        Button*[2] buttonPairs;
        Button* aTeamButtons;
        Button* bTeamButtons;

        H2HControls(const int numberOfButtons)
            : numButtons(numberOfButtons)
        {
            buttons = new *Button[numButtons];


            // setup buttons in main button array
            switch (numButtons)
            {
            }
    }

}
