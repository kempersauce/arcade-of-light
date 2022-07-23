#pragma once

#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

// Use these with the Teensy Audio Shield
// This uses the audio shield's card reader
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14

// Sounds
AudioControlSGTL5000 sgtl5000_1;
AudioOutputI2S i2s1;

void initAudio() {
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!SD.begin(SDCARD_CS_PIN)) {
    Serial.println("Unable to access the SD card during audio setup");
  }
}
