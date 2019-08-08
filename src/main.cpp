#include <H2HDisplay.h>
#include <H2HTest.h>
#include <LifeGame.h>

Game* game;

void setup()
{
    Serial.begin(9600);
    Serial.println("Begin setup()");

    // Choose your Display type
    Display* gameDisplay = new H2HDisplay();
    Serial.println("gameDisplay created");

    // Choose your Game type
    game = (Game*)new H2HTest(gameDisplay);
    Serial.println("game created");

    game->setup();
    Serial.println("game setup complete");

    Serial.println("End setup()");
}

void loop() {
    game->loop();
}
