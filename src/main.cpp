#include <H2HDisplay.h>
#include <LifeGame.h>

Game* game;

void setup() {
    // Choose your Display type
    Display* gameDisplay = new H2HDisplay();

    // Choose your Game type
    game = (Game*)new LifeGame(gameDisplay);
    game->setup();
}

void loop() {
    game->loop();
}
