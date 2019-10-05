
#include <Arduino.h>
#include <FastLED.h>
#include <Display.h>
#include <H2HDisplay.h>
#include <Game.h>
#include <RocketGame.h>


Game* game;
Display* gameDisplay;




void setup()
{
    gameDisplay = (Display*)new H2HDisplay();
    game = (Game*)new RocketGame(gameDisplay);
    game->setup();
    FastLED.show();
    Serial5.begin(9600);
}
void loop()
{
    game->loop();
    FastLED.show();
}