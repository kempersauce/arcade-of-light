#pragma once

#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

#include "serial/debug.h"  // for debug::*

namespace kss {
namespace audio {

// Use these with the Teensy Audio Shield
// This uses the audio shield's card reader
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14

// Sounds
AudioControlSGTL5000 sgtl5000_1;
AudioOutputI2S audioOutput;

void InitAudio() {
  AudioMemory(16);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  while (!SD.begin(SDCARD_CS_PIN)) {
    debug::println("Unable to access the SD card! Retrying in 500ms...");
    delay(500);
  }
}

}  // namespace audio
}  // namespace kss
