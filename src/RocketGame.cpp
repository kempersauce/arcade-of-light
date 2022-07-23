// #include <Arduino.h>
// #include <FastLED.h>
// #include <Display.h>
// #include <RocketDisplay.h>
// #include <H2HDisplay.h>
// #include <Game.h>
// #include <RocketGame.h>
// #include <AudioSender.h>
// #include <hardware_simple.h>  // For kss::controls::hardware::Simple

// RocketGame* game;
// Display* gameDisplay;
// kss::controls::hardware::Simple controls;

// void setup()
// {
//     gameDisplay = (Display*) new RocketDisplay();

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