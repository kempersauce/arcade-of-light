//working audio example

#include <Game.h>
#include <Button.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Sounds.h>

// Use these with the Teensy Audio Shield
//This uses the audio shield's card reader
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// TODO move these into the WavPLayer class
AudioPlaySdWav           playSdWav1;
AudioPlaySdWav           playSdWav2;
AudioPlaySdWav           playSdWav3;
AudioPlaySdWav           playSdWav4;

AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav2, 0, i2s1, 1);
AudioConnection          patchCord3(playSdWav3, 0, i2s1, 2);
AudioConnection          patchCord4(playSdWav4, 0, i2s1, 3);


class WavPlayer : Game
{
private:

    //Buttons go here
    Button ABut = Button(24);
    Button BBut = Button(25);
    Button CBut = Button(26);
    Button DBut = Button(27);
    Button EBut = Button(28);
    Button FBut = Button(29);

public:
    void setup()
    {
        Serial.begin(9600);
        initAudio();
        delay(1000);
    }

    void loop()
    {
       // if (playSdWav1.isPlaying() == false) {
          if (ABut.isPressed())
          {
              playSdWav2.play("Guycey1.wav");
              Serial.println("Button A Pressed");
              delay(500);
          }

          if (BBut.isPressed())
          {
              playSdWav1.play("WEEK1.WAV");
              Serial.println("Button B Pressed");
              delay(500);
          }

          if (CBut.isPressed())
          {
              playSdWav1.play("WEEK2.WAV");
              Serial.println("Button C Pressed");
              delay(500);
          }

          if (DBut.isPressed())
          {
              playSdWav1.play("WEEK3.WAV");
              Serial.println("Button D Pressed");
              delay(500);
          }

          if (EBut.isPressed())
          {
            playSdWav1.play("WEEK4.WAV");
            Serial.println("Button E Pressed");
            delay(500);
          }

          if (FBut.isPressed())
          {
              playSdWav1.play("Gladiat.wav");
              Serial.println("Button F Pressed");
              delay(500);
          }
      //  }
    }
};
