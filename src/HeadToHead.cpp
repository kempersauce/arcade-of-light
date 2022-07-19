
// #include <Arduino.h>
// #include <FastLED.h>
// #include <Display.h>
// #include <H2HDisplay.h>
// #include <Game.h>
// #include <Head2Head.h>
// #include <hardware_simple.h>
// #include <H2HControl.h>


// Game* game;
// Display* gameDisplay;
// kss::controls::hardware::Simple controls;

// void setup()
// {
//     gameDisplay = (Display*)new H2HDisplay();

//     H2HControl teamA;
//     teamA.buttons[0] = controls.CreateButton(H2H_BUTTON_PIN_7);
//     teamA.buttons[1] = controls.CreateButton(H2H_BUTTON_PIN_6);
//     teamA.buttons[2] = controls.CreateButton(H2H_BUTTON_PIN_5);
//     teamA.buttons[3] = controls.CreateButton(H2H_BUTTON_PIN_4);
//     teamA.buttons[4] = controls.CreateButton(H2H_BUTTON_PIN_3);
//     teamA.buttons[5] = controls.CreateButton(H2H_BUTTON_PIN_2);
//     teamA.buttons[6] = controls.CreateButton(H2H_BUTTON_PIN_1);
//     teamA.buttons[7] = controls.CreateButton(H2H_BUTTON_PIN_0);

//     H2HControl teamB;
//     teamB.buttons[0] = controls.CreateButton(H2H_BUTTON_PIN_8);
//     teamB.buttons[1] = controls.CreateButton(H2H_BUTTON_PIN_9);
//     teamB.buttons[2] = controls.CreateButton(H2H_BUTTON_PIN_10);
//     teamB.buttons[3] = controls.CreateButton(H2H_BUTTON_PIN_11);
//     teamB.buttons[4] = controls.CreateButton(H2H_BUTTON_PIN_12);
//     teamB.buttons[5] = controls.CreateButton(H2H_BUTTON_PIN_13);
//     teamB.buttons[6] = controls.CreateButton(H2H_BUTTON_PIN_14);
//     teamB.buttons[7] = controls.CreateButton(H2H_BUTTON_PIN_15);

//     game = (Game*)new Head2Head(gameDisplay, teamA, teamB);
//     game->setup();
//     FastLED.show();
// }

// void loop()
// {
//     controls.PollAll();
//     game->loop();
//     FastLED.show();
// }