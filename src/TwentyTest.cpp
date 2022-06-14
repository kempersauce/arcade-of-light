
#include <Arduino.h>
#include <FastLED.h>
#include <Display.h>
#include <TwentyDisplay.h>
#include <Game.h>
#include <NoiseGame.h>


Game* game;
Display* gameDisplay;

void setup()
{
    gameDisplay = (Display*)new TwentyDisplay();

    game = (Game*)new NoiseGame(gameDisplay);
    game->setup();
    FastLED.show();
}

void loop()
{
    game->loop();
    FastLED.show();
}