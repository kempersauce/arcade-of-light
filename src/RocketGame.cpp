#include <Arduino.h>
#include <FastLED.h>
#include <Display.h>
#include <H2HDisplay.h>
#include <Game.h>
#include <RocketGame.h>
#include <AudioSender.h>


RocketGame* game;
Display* gameDisplay;
AudioSender* audio;



void setup()
{
    gameDisplay = (Display*)new H2HDisplay();
    game = new RocketGame(gameDisplay);
    audio = new AudioSender();
    game->setup();
    FastLED.show();
    audio->playWav("FUEL100");
}
void loop()
{
    game->loop();
    FastLED.show();
}