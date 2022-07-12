
// #include <Arduino.h>
// #include <FastLED.h>
// #include <FiveDisplay.h>
// #include <LifeGameSinglePlayer.h>
// #include <Game.h>
// #include <simple.h>  // for controls::hardware::Simple


// Game* game;
// Display* gameDisplay;
// controls::hardware::Simple controls;

// void setup()
// {
//     gameDisplay = (Display*)new FiveDisplay();

//     DirPad dirPad{
//         controls.CreateButton(BUTTON_PIN_4),
//         controls.CreateButton(BUTTON_PIN_3),
//         controls.CreateButton(BUTTON_PIN_5),
//         controls.CreateButton(BUTTON_PIN_2),
//         controls.CreateButton(BUTTON_PIN_1),
//         controls.CreateButton(BUTTON_PIN_0)
//     }

//     game = (Game*)new LifeGameSinglePlayer(gameDisplay, dirPad);
//     game->setup();
//     FastLED.show();
// }

// void loop()
// {
//     controls.PollAll();
//     game->loop();
//     FastLED.show();
// }