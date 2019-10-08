
#include <Arduino.h>
#include <FastLED.h>
#include <Display.h>
#include <LifeGameSinglePlayer.h>
#include <Game.h>
#include <Head2Head.h>


Game* game;
Display* gameDisplay;

void setup()
{
    gameDisplay = (Display*)new H2HDisplay();

    game = (Game*)new LifeGameSinglePlayer(gameDisplay);
    game->setup();
    FastLED.show();
}
void loop()
{
    game->loop();
    FastLED.show();
}