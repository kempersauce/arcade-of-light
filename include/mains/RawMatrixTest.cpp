
#include <Arduino.h>
#include <FastLED.h>

#include "serial/debug.h"  // for Debug

int cont[4] = {2, 3, 4, 7};
int butt[4] = {8, 9, 10, 11};
// int butt[6] = {8,9,10,11,12,13};
int controllerNum = 4;
int buttonNum = 4;

void setup() {
  // Make controller pins outputs
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);

  // Make button pins inputs
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  // pinMode(12, INPUT);
  // pinMode(13, INPUT);

  debug::Init();

  digitalWrite(cont[0], LOW);
  digitalWrite(cont[1], HIGH);
  digitalWrite(cont[2], HIGH);
  digitalWrite(cont[3], HIGH);

  for (int button = 0; button < buttonNum; button++) {
    if (digitalRead(butt[button]) == HIGH) {
      Debug("button " + button + " reporting for duty");
    }
  }
}

void loop() {
  for (int controller = 0; controller < controllerNum; controller++) {
    digitalWrite(cont[controller], LOW);
    // Allow the signal to settle before polling
    delayMicroseconds(5);

    for (int button = 0; button < buttonNum; button++) {
      if (digitalRead(butt[button]) == LOW) {
        Debug("controller=" + controller + " button=" + button);
      }
    }
    digitalWrite(cont[controller], HIGH);
  }
}