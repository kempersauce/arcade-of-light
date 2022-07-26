
// #include <Arduino.h>
// #include <FastLED.h>
// #include "display/display.h"  // for kss::display::Display
// #include "display/h2h.h"  // for H2HDisplay
// #include "games/game.h"  // for Game
// #include "games/head2head/head2head.h"  // for Head2Head
// #include "controls/hardware/simple.h"
// #include "controls/h2h_controller.h"  // for H2HController

// Game* game;
// kss::display::Display* gameDisplay;
// kss::controls::hardware::Simple controls;

// void setup()
// {
//     gameDisplay = (kss::display::Display*)new kss::display::H2HDisplay();

//     kss::controls::H2HController teamA;
//     teamA.buttons[0] = controls.CreateButton(H2H_BUTTON_PIN_7);
//     teamA.buttons[1] = controls.CreateButton(H2H_BUTTON_PIN_6);
//     teamA.buttons[2] = controls.CreateButton(H2H_BUTTON_PIN_5);
//     teamA.buttons[3] = controls.CreateButton(H2H_BUTTON_PIN_4);
//     teamA.buttons[4] = controls.CreateButton(H2H_BUTTON_PIN_3);
//     teamA.buttons[5] = controls.CreateButton(H2H_BUTTON_PIN_2);
//     teamA.buttons[6] = controls.CreateButton(H2H_BUTTON_PIN_1);
//     teamA.buttons[7] = controls.CreateButton(H2H_BUTTON_PIN_0);

//     kss::controls::H2HController teamB;
//     teamB.buttons[0] = controls.CreateButton(H2H_BUTTON_PIN_8);
//     teamB.buttons[1] = controls.CreateButton(H2H_BUTTON_PIN_9);
//     teamB.buttons[2] = controls.CreateButton(H2H_BUTTON_PIN_10);
//     teamB.buttons[3] = controls.CreateButton(H2H_BUTTON_PIN_11);
//     teamB.buttons[4] = controls.CreateButton(H2H_BUTTON_PIN_12);
//     teamB.buttons[5] = controls.CreateButton(H2H_BUTTON_PIN_13);
//     teamB.buttons[6] = controls.CreateButton(H2H_BUTTON_PIN_14);
//     teamB.buttons[7] = controls.CreateButton(H2H_BUTTON_PIN_15);

//     game = (Game*)new kss::games::h2h::Head2Head(gameDisplay, teamA, teamB);
//     game->setup();
//     FastLED.show();
// }

// void loop()
// {
//     controls.PollAll();
//     game->loop();
//     FastLED.show();
// }