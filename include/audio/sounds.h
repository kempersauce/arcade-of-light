#pragma once

#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

#include "serial/debug.h"  // for Debug

namespace kss {
namespace audio {

// Use these with the Teensy Audio Shield
// This uses the audio shield's card reader
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14

// Sounds
constexpr float kAudioVolume{0.5};
AudioControlSGTL5000 sgtl5000_1;

void InitSDCard() {
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  while (!SD.begin(SDCARD_CS_PIN)) {
    Debug("Unable to access the SD card! Retrying in 500ms...");
    delay(500);
  }
  Debug("SD Card Initialized");
}

void Init(bool init_sd_card = true) {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(500);

  // Enable audio output
  sgtl5000_1.enable();
  sgtl5000_1.volume(kAudioVolume);

  if (init_sd_card) {
    InitSDCard();
  } else {
    Debug("Skipping SD Card Initialization");
  }

  Debug("Audio Initialized!!");
}

inline void AudioDebug() {
  Debug("Proc=" + AudioProcessorUsage() + " (max=" + AudioProcessorUsageMax() +
        "), Mem=" + AudioMemoryUsage() + " (max=" + AudioMemoryUsageMax() +
        ")");
}

}  // namespace audio
}  // namespace kss
