
// #include <Arduino.h>
// #include <FastLED.h>
// #include "display/five.h"  // for FiveDisplay
// #include "controls/dir_pad.h"
// #include "games/life/life_single_player.h"  // for LifeGameSinglePlayer
// #include "games/game.h"  // for Game
// #include "controls/hardware/simple.h"  // for kss::controls::hardware::Simple

// Game* game;
// Display* gameDisplay;
// kss::controls::hardware::Simple controls;

// void setup()
// {
//     gameDisplay = (Display*)new FiveDisplay();

//     kss::controls::DirPad dirPad{
//         controls.CreateButton(BUTTON_PIN_4),
//         controls.CreateButton(BUTTON_PIN_3),
//         controls.CreateButton(BUTTON_PIN_5),
//         controls.CreateButton(BUTTON_PIN_2),
//         controls.CreateButton(BUTTON_PIN_1),
//         controls.CreateButton(BUTTON_PIN_0)
//     };

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