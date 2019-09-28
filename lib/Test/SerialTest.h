#include <Game.h>
#include <SingleColorBG.h>
#include <KemperSerialReceiver.h>

class SerialTest : Game
{
    KemperSerialReceiver *ks;

public:
    SerialTest(Display *gameDisplay)
        : Game(gameDisplay)
    {
        background = (Animation *)new SingleColorBG(0, 0, 255);
    }

    void setup()
    {
        ks = new KemperSerialReceiver(Serial1);
        delay(4000);
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        Serial.print("starting Serial Test");

    }

    void loop()
    {
        background->draw(display);

        if (ks->recvWithStartEndMarkers())
        {
            char output[32];
            ks->getNextMessage(output);

            Serial.print("\noutput:");
            Serial.print(output);

        }
    }
};
