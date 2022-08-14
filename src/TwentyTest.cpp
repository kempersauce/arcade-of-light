// #include <Arduino.h>
// #include <FastLED.h>
// #include "display/display.h"  // for Display
// #include "display/twenty.h"  // for TwentyDisplay
// #include "games/game.h"  // for Game
// #include "games/noise/noise.h"  // for NoiseGame

// Game* game;
// kss::display::Display* gameDisplay;

// void setup()
// {
//     gameDisplay = (kss::display::Display*)new kss::display::TwentyDisplay();

//     game = (Game*)new kss::games::noise::NoiseGame(gameDisplay);
//     game->setup();
//     gameDisplay->Show();
// }

// void loop()
// {
//     game->loop();
//     gameDisplay->Show();
// }