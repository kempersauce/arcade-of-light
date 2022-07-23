// working audio example

#include <Audio.h>
#include <Game.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Sounds.h>
#include <Wire.h>
#include "controls/button.h"

#include <memory>  // For shared_ptr

// Use these with the Teensy Audio Shield
// This uses the audio shield's card reader
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14

// TODO move these into the WavPLayer class
AudioPlaySdWav playSdWav1;
AudioPlaySdWav playSdWav2;
AudioPlaySdWav playSdWav3;
AudioPlaySdWav playSdWav4;

AudioConnection patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection patchCord2(playSdWav2, 0, i2s1, 1);
AudioConnection patchCord3(playSdWav3, 0, i2s1, 2);
AudioConnection patchCord4(playSdWav4, 0, i2s1, 3);

class WavPlayer : Game {
 private:
  // Buttons go here
  std::shared_ptr<kss::controls::Button> ABut;
  std::shared_ptr<kss::controls::Button> BBut;
  std::shared_ptr<kss::controls::Button> CBut;
  std::shared_ptr<kss::controls::Button> DBut;
  std::shared_ptr<kss::controls::Button> EBut;
  std::shared_ptr<kss::controls::Button> FBut;

 public:
  WavPlayer(std::shared_ptr<kss::controls::Button> aBut,
            std::shared_ptr<kss::controls::Button> bBut,
            std::shared_ptr<kss::controls::Button> cBut,
            std::shared_ptr<kss::controls::Button> dBut,
            std::shared_ptr<kss::controls::Button> eBut,
            std::shared_ptr<kss::controls::Button> fBut)
      : ABut{std::move(aBut)},
        BBut{std::move(bBut)},
        CBut{std::move(cBut)},
        DBut{std::move(dBut)},
        EBut{std::move(eBut)},
        FBut{std::move(fBut)} {}

  void setup() {
    Serial.begin(9600);
    initAudio();
    delay(1000);
  }

  void loop() {
    // if (playSdWav1.isPlaying() == false) {
    if (ABut->IsPressed()) {
      playSdWav2.play("Guycey1.wav");
      Serial.println("Button A Pressed");
      delay(500);
    }

    if (BBut->IsPressed()) {
      playSdWav1.play("WEEK1.WAV");
      Serial.println("Button B Pressed");
      delay(500);
    }

    if (CBut->IsPressed()) {
      playSdWav1.play("WEEK2.WAV");
      Serial.println("Button C Pressed");
      delay(500);
    }

    if (DBut->IsPressed()) {
      playSdWav1.play("WEEK3.WAV");
      Serial.println("Button D Pressed");
      delay(500);
    }

    if (EBut->IsPressed()) {
      playSdWav1.play("WEEK4.WAV");
      Serial.println("Button E Pressed");
      delay(500);
    }

    if (FBut->IsPressed()) {
      playSdWav1.play("Gladiat.wav");
      Serial.println("Button F Pressed");
      delay(500);
    }
    //  }
  }
};
