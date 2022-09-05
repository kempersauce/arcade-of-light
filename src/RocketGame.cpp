// #include <Arduino.h>
// #include <FastLED.h>
// #include "display/display.h"  // for Display
// #include "display/rocket.h"  // for RocketDisplay
// #include "display/h2h.h"  // for H2HDisplay
// #include "games/game.h"  // for Game
// #include "games/rocket/rocket_game.h"  // for RocketGame
// #include "controls/hardware/simple.h"  // for controls::hardware::Simple

// using namespace kss::display;
// using namespace kss::controls::hardware;
// using namespace kss::games::rocket;

// RocketDisplay* gameDisplay = new RocketDisplay();
// Simple controls;
// RocketGame* game = new RocketGame(gameDisplay,
//         controls.CreateButton(BUTTON_PIN_0),
//         controls.CreateButton(BUTTON_PIN_1));

// void setup()
// {
//     game->setup();
// }

// void loop()
// {
//     controls.PollAll();
//     game->loop();
//     gameDisplay->Show();
// }