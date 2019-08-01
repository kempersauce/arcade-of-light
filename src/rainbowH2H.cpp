#include <Arduino.h>
#include <FastLED.h>
#include <H2HTest.h>

Game* gameBow;

void setup() {
    Display* gameBowDisplay = new H2HDisplay();
    gameBow = (Game*)new H2HTest(gameBowDisplay);
    gameBow->setup();
}

void loop() {
    gameBow->loop();
}
