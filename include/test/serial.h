#include "animation/single_color_background.h"  // for SingleColorBG
#include "games/game.h"                         // for Game
#include "serial/receiver.h"                    // for Receiver

class SerialTest : Game {
  KemperSerialReceiver ks;

  SingleColorBG background;

 public:
  SerialTest(Display *gameDisplay)
      : Game(gameDisplay), background(0, 0, 255), ks(&Serial1) {}

  void setup() {
    delay(4000);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("starting Serial Test");
  }

  void loop() {
    background.draw(display);

    if (ks.recvWithStartEndMarkers()) {
      char output[32];
      ks.getNextMessage(output);

      Serial.print("\noutput:");
      Serial.print(output);
    }
  }
};
