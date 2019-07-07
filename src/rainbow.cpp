#include <Arduino.h>
#include <FastLED.h>
#include <GameBow.h>

Game gameBow;

void setup() {
    Display gameBowDisplay = new Display(5,300);
    gameBow = new GameBow(gameBowDisplay);
    gameBow.setup();
}
void loop(){
    gameBow.loop();
}
