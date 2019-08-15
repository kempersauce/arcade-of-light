#include <H2HDisplay.h>
#include <H2HTest.h>
#include <LifeGame.h>
#include <Head2Head.h>
#include <RocketGame.h>

Game* game;
Display* gameDisplay;

void setup()
{
    //delay(15 * 1000);
    Serial.begin(9600);
    Serial.println("Begin setup()");

    // Choose your Display type
    gameDisplay = (Display*)new H2HDisplay();

    // debug set strip0 red
    for (int i = 0; i < gameDisplay->lengthStrips; i++)
    {
        gameDisplay->strips[0][i] = CRGB::Red;
    }
    Serial.println("gameDisplay created");
    FastLED.show();

    // Choose your Game type
    game = (Game*)new RocketGame(gameDisplay);

    // debug set strip0 yellow
    for (int i = 0; i < gameDisplay->lengthStrips; i++)
    {
        gameDisplay->strips[0][i] = CRGB::Yellow;
    }
    Serial.println("game created");
    FastLED.show();

    game->setup();

    // debug set strip0 green
    for (int i = 0; i < gameDisplay->lengthStrips; i++)
    {
        gameDisplay->strips[0][i] = CRGB::Green;
    }
    Serial.println("game setup complete");
    FastLED.show();

    Serial.println("End setup()");
    FastLED.show();
}

void loop()
{
    // debug set strip0 blue
    for (int i = 0; i < gameDisplay->lengthStrips; i++)
    {
        gameDisplay->strips[0][i] = CRGB::Blue;
    }
    // Serial.println("loop() entered");

    game->loop();
    FastLED.show();
}
