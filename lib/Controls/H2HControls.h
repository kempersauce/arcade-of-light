#include <Button.h>
#include <H2HConstants.h>

class H2HControls {
    public:
        const int numButtons;
        Button* buttons;
        Button*[2] buttonPairs;
        Button* ATeamButtons;
        Button* BTeamButtons;

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
