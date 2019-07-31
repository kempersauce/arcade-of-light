#include <Arduino.h>
#include <FastLED.h>
#include <H2HTest.h>

H2HGame* gameBow;

void setup() {
    H2HDisplay* gameBowDisplay = new H2HDisplay(8,123);
    gameBow = (H2HGame*)new H2HTest(gameBowDisplay);
    gameBow->setup();
}

void loop() {
    gameBow->loop();
}
