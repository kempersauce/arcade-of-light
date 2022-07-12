#pragma once

#include <button.h>
#include <Constants.h>

class H2HControls {
    public:
        Button** teamA;
        Button** teamB;

        H2HControls()
        {
            teamA = new Button*[8] {
                new Button(H2H_BUTTON_PIN_7),
                new Button(H2H_BUTTON_PIN_6),
                new Button(H2H_BUTTON_PIN_5),
                new Button(H2H_BUTTON_PIN_4),
                new Button(H2H_BUTTON_PIN_3),
                new Button(H2H_BUTTON_PIN_2),
                new Button(H2H_BUTTON_PIN_1),
                new Button(H2H_BUTTON_PIN_0),
            };

            teamB = new Button*[8] {
                new Button(H2H_BUTTON_PIN_8),
                new Button(H2H_BUTTON_PIN_9),
                new Button(H2H_BUTTON_PIN_10),
                new Button(H2H_BUTTON_PIN_11),
                new Button(H2H_BUTTON_PIN_12),
                new Button(H2H_BUTTON_PIN_13),
                new Button(H2H_BUTTON_PIN_14),
                new Button(H2H_BUTTON_PIN_15),
            };
        }

        void pollAll()
        {
            for (int i = 0; i < 8; i++)
            {
                teamA[i]->poll();
                teamB[i]->poll();
            }
        }
    };
