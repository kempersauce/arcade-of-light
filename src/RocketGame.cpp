// #include <Arduino.h>
// #include <FastLED.h>
// #include "display/display.h"  // for kss::display::Display
// #include "display/rocket.h"  // for RocketDisplay
// #include "display/h2h.h"  // for H2HDisplay
// #include "games/game.h"  // for Game
// #include "games/rocket/rocket_game.h"  // for RocketGame
// #include "controls/hardware/simple.h"  // For kss::controls::hardware::Simple

// RocketGame* game;
// kss::display::Display* gameDisplay;
// kss::controls::hardware::Simple controls;

// void setup()
// {
//     gameDisplay = (kss::display::Display*) new RocketDisplay();

//     game = new RocketGame(gameDisplay,
//         controls.CreateButton(BUTTON_PIN_0),
//         controls.CreateButton(BUTTON_PIN_1));

//     game->setup();
//     FastLED.show();
// }

// void loop()
// {
//     controls.PollAll();
//     game->loop();
//     FastLED.show();
// }