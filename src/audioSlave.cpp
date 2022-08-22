#include <Arduino.h>
#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

#include <iostream>
#include <string>

#include "serial/debug.h"     // for debug::*
#include "serial/receiver.h"  // for Receiver

// Use these with the Teensy Audio Shield
// This uses the audio shield's card reader

const size_t kChannelCount = 5;
AudioPlaySdWav playSdWav[kChannelCount];

// CHannel 0 is background
AudioPlaySdWav& playSdWavBG = playSdWav[0];

AudioOutputI2S audioOutput;

AudioMixer4 mixer1;
AudioMixer4 mixer2;
AudioMixer4 bgMixer;
AudioMixer4 effectMixer;
AudioMixer4 mixMaster;

// Sound effect channels to mixers

AudioConnection patchCord1a(playSdWav[1], 0, mixer1, 0);
AudioConnection patchCord1b(playSdWav[1], 1, mixer1, 1);
AudioConnection patchCord2a(playSdWav[2], 0, mixer1, 2);
AudioConnection patchCord2b(playSdWav[2], 1, mixer1, 3);
AudioConnection patchCord3a(playSdWav[3], 0, mixer2, 0);
AudioConnection patchCord3b(playSdWav[3], 1, mixer2, 1);
AudioConnection patchCord4a(playSdWav[4], 0, mixer2, 2);
AudioConnection patchCord4b(playSdWav[4], 1, mixer2, 3);

// Sound effects to single mixer
AudioConnection patchCordEffects1a(mixer1, 0, effectMixer, 0);
AudioConnection patchCordEffects1b(mixer1, 1, effectMixer, 1);
AudioConnection patchCordEffects2a(mixer2, 0, effectMixer, 2);
AudioConnection patchCordEffects2b(mixer2, 1, effectMixer, 3);

// Background Sound Effects to Background Mixer
AudioConnection patchCordBG1a(playSdWavBG, 0, bgMixer, 0);
AudioConnection patchCordBG1b(playSdWavBG, 1, bgMixer, 1);

// Effects and Background to Master Mixer
AudioConnection patchCordToMaster1a(effectMixer, 0, mixMaster, 0);
AudioConnection patchCordToMaster1b(effectMixer, 1, mixMaster, 1);
AudioConnection patchCordToMaster2a(bgMixer, 0, mixMaster, 2);
AudioConnection patchCordToMaster2b(bgMixer, 1, mixMaster, 3);

// Master Mixer out
AudioConnection patchCordOut1a(mixMaster, 0, audioOutput, 0);
AudioConnection patchCordOut1b(mixMaster, 1, audioOutput, 1);

AudioControlSGTL5000 sgtl5000_1;

char* lastOutput1;
char* lastOutput2;
std::string backgroundName;
bool hasBackGround = false;
bool hasNewBackGround = false;
bool backgroundIsPlaying = false;
uint32_t backgroundStartMillis;
uint32_t backgroundLengthMillis = 1000;
const uint32_t backgroundCheckWait = 1000;
float mixerGain = 0.7;

#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14

inline String ChannelLabel(const size_t channel) {
  if (channel == 0) {
    return (String) "CHANNEL " + channel + " (BACKGROUND)";
  } else {
    return (String) "CHANNEL " + channel;
  }
}

inline void PrintFileInfo(const size_t channel, const char* fileName) {
  debug::println(ChannelLabel(channel));
  debug::println((String) "FILE:    " + fileName);
  debug::println("========================================");
}

inline void CheckChannelIndex(const int line_no, const size_t channel) {
  if (channel >= kChannelCount) {
    debug::println((String) "ERROR (line " + line_no + "): channel " + channel +
                   " is out of bounds (max is " + (kChannelCount - 1) + ")");
  }
}

#define CheckChannel(channel) CheckChannelIndex(__LINE__, channel)

kss::serial::Receiver serialReceiver[]{
    // kss::serial::Receiver(&Serial1),
    // kss::serial::Receiver(&Serial2),
    // kss::serial::Receiver(&Serial3),
    kss::serial::Receiver(&Serial4), kss::serial::Receiver(&Serial5)};

void StopChannel(const size_t channel) {
  CheckChannel(channel);
  playSdWav[channel].stop();

  debug::println(ChannelLabel(channel) + ": STOPPED");
  debug::println("========================================");
}

void StartChannel(const size_t channel, const char* fileName) {
  CheckChannel(channel);
  playSdWav[channel].play(fileName);
  PrintFileInfo(channel, fileName);
}

void StartBGChannel(const std::string& fileName) {
  StartChannel(0, fileName.c_str());
}

void BackgroundTimeCheck() {
  const uint32_t currentTime = millis();
  const uint32_t timeElapsed = currentTime - backgroundStartMillis;
  if (timeElapsed > backgroundCheckWait) {
    if (!playSdWavBG.isPlaying()) {
      backgroundIsPlaying = false;
      // hasNewBackGround = true;
      debug::println((String) "BG checkWait: " + backgroundCheckWait);
      debug::println((String) "BG Elapsed:   " + timeElapsed);
      debug::println((String) "BG isPlaying: " + backgroundIsPlaying);
      debug::println("===============================");
    }
  }
}

void PlayBG() {
  if (!backgroundIsPlaying && hasBackGround) {
    StartBGChannel(backgroundName);
    backgroundIsPlaying = true;
    backgroundStartMillis = millis();
    backgroundLengthMillis = playSdWavBG.lengthMillis();
    // hasNewBackGround = false;
  } else if (backgroundIsPlaying) {
    backgroundLengthMillis = playSdWavBG.lengthMillis();
    BackgroundTimeCheck();
  }
}

void SetBG(char* fileName) {
  playSdWavBG.stop();
  backgroundIsPlaying = false;
  hasBackGround = true;
  backgroundName = fileName;
  debug::println((String)backgroundName.c_str());
  debug::println((String) "BG STATUS: " + (String)playSdWavBG.isPlaying());
  PlayBG();
}

size_t GetIdleChannel() {
  const static size_t first_channel = 3;

  // Find first available channel, starting with first_channel
  for (size_t channel = first_channel; channel < kChannelCount; ++channel) {
    if (!playSdWav[channel].isPlaying()) {
      return channel;
    }
  }

  // Default to first_channel if they're all already playing something
  debug::println("OVERWRITE==OVERWRITE==OVERWRITE (all channels playing)");
  return first_channel;
}

void PlayWav(const char* fileName) {
  const size_t channel = GetIdleChannel();
  StartChannel(channel, fileName);
}

//=============================================================================//
// SETUP AND LOOP
void setup() {
  Serial.begin(115200);
  AudioMemory(16);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  while (!SD.begin(SDCARD_CS_PIN)) {
    debug::println("Unable to access the SD card! Retrying in 500ms...");
    delay(500);
  }

  mixMaster.gain(0, 0.5);
  mixMaster.gain(1, 0.5);
  mixer1.gain(0, mixerGain);
  mixer1.gain(1, mixerGain);
  mixer1.gain(2, mixerGain);
  mixer1.gain(3, mixerGain);
  mixer2.gain(0, mixerGain);
  mixer2.gain(1, mixerGain);
  mixer2.gain(2, mixerGain);
  mixer2.gain(3, mixerGain);
  effectMixer.gain(0, mixerGain);
  effectMixer.gain(1, mixerGain);
  effectMixer.gain(2, mixerGain);
  effectMixer.gain(3, mixerGain);
  bgMixer.gain(0, mixerGain);
  bgMixer.gain(1, mixerGain);
  bgMixer.gain(2, mixerGain);
  bgMixer.gain(3, mixerGain);

  PlayWav("FUEL100.WAV");
  delay(50);
  PlayWav("FUEL50.WAV");
  // delay(5000);

  // setBG("<MOONJAZZ.WAV>");

  // playSdWavBG.play("BOOM.WAV");
  debug::println("starting the loop");
}

void channelChecker(char* message) {
  char channelChar = message[0];
  char channelNum = channelChar - '0';
  char isStart = message[1];
  if (channelNum == 1 || channelNum == 2) {
    char* trimmedOutput = message;
    trimmedOutput++;
    trimmedOutput++;
    if (isStart == '1') {
      StartChannel(channelNum, trimmedOutput);
    } else if (isStart == '0') {
      StopChannel(channelNum);
    }
  } else if (channelNum == 9) {
    char* trimmedOutput = message;
    trimmedOutput++;
    SetBG(trimmedOutput);
  } else {
    PlayWav(message);
  }
}

void loop() {
  PlayBG();
  for (int i = 0; i < 2; i++) {
    serialReceiver[i].recvWithStartEndMarkers();
    while (serialReceiver[i].hasMessages()) {
      char output[32];
      serialReceiver[i].getNextMessage(output);
      debug::println((String) "playing from serial[" + i + "]: " + output);
      char channelChar = output[0];
      char channelNum = channelChar - '0';
      char isStart = output[1];
      channelChecker(output);
    }
  }
}
