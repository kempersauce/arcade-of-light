// #include <Audio.h>
// #include <SD.h>
// #include <SPI.h>
// #include <SerialFlash.h>
// #include <Wire.h>

// #include <iostream>
// #include <string>

// #include "audio/sounds.h"     // for initAudio
// #include "serial/debug.h"     // for debug::*
// #include "serial/receiver.h"  // for Receiver

// using namespace kss;

// // Use these with the Teensy Audio Shield
// // This uses the audio shield's card reader

// const size_t kChannelCount = 5;
// AudioPlaySdWav playSdWav[kChannelCount];

// AudioMixer4 mixer1;
// AudioMixer4 mixer2;
// AudioMixer4 bgMixer;
// AudioMixer4 effectMixer;
// AudioMixer4 mixMaster;

// // Sound effect channels to mixers

// AudioConnection patchCordBGa(playSdWav[0], 0, bgMixer, 0);
// AudioConnection patchCordBGb(playSdWav[0], 1, bgMixer, 1);

// AudioConnection patchCord1a(playSdWav[1], 0, mixer1, 0);
// AudioConnection patchCord1b(playSdWav[1], 1, mixer1, 1);
// AudioConnection patchCord2a(playSdWav[2], 0, mixer1, 2);
// AudioConnection patchCord2b(playSdWav[2], 1, mixer1, 3);

// AudioConnection patchCord3a(playSdWav[3], 0, mixer2, 0);
// AudioConnection patchCord3b(playSdWav[3], 1, mixer2, 1);
// AudioConnection patchCord4a(playSdWav[4], 0, mixer2, 2);
// AudioConnection patchCord4b(playSdWav[4], 1, mixer2, 3);

// // Sound effects to single mixer
// AudioConnection patchCordEffects1a(mixer1, 0, effectMixer, 0);
// AudioConnection patchCordEffects1b(mixer1, 1, effectMixer, 1);
// AudioConnection patchCordEffects2a(mixer2, 0, effectMixer, 2);
// AudioConnection patchCordEffects2b(mixer2, 1, effectMixer, 3);

// // Effects and Background to Master Mixer
// AudioConnection patchCordToMaster1a(effectMixer, 0, mixMaster, 0);
// AudioConnection patchCordToMaster1b(effectMixer, 1, mixMaster, 1);
// AudioConnection patchCordToMaster2a(bgMixer, 0, mixMaster, 2);
// AudioConnection patchCordToMaster2b(bgMixer, 1, mixMaster, 3);

// // Master Mixer out
// AudioConnection patchCordOut1a(mixMaster, 0, audio::audioOutput, 0);
// AudioConnection patchCordOut1b(mixMaster, 1, audio::audioOutput, 1);

// float mixerGain = 0.7;

// inline String ChannelLabel(const size_t channel) {
//   if (channel == 0) {
//     return (String) "CHANNEL " + channel + " (BACKGROUND)";
//   } else {
//     return (String) "CHANNEL " + channel;
//   }
// }

// inline void PrintFileInfo(const size_t channel, const char* fileName) {
//   debug::println(ChannelLabel(channel));
//   debug::println((String) "FILE:    " + fileName);
//   debug::println("========================================");
// }

// inline void CheckChannelIndex(const int line_no, const size_t channel) {
//   if (channel >= kChannelCount) {
//     debug::println((String) "ERROR (line " + line_no + "): channel " + channel +
//                    " is out of bounds (max is " + (kChannelCount - 1) + ")");
//   }
// }

// #define CheckChannel(channel) CheckChannelIndex(__LINE__, channel)

// serial::Receiver serialReceiver[]{
//     serial::Receiver(&Serial1),
//     // serial::Receiver(&Serial2), // TX2 & RX2 are used by audioshield
//     // serial::Receiver(&Serial3), // AudioShield uses RX3 for volume control
//     serial::Receiver(&Serial4),
//     // serial::Receiver(&Serial5), // TX5 & RX5 are used by audioshield
//     serial::Receiver(&Serial6), serial::Receiver(&Serial7)};

// void StopChannel(const size_t channel) {
//   CheckChannel(channel);
//   playSdWav[channel].stop();

//   debug::println(ChannelLabel(channel) + ": STOPPED");
//   debug::println("========================================");
// }

// void StartChannel(const size_t channel, const char* fileName) {
//   CheckChannel(channel);
//   if (playSdWav[channel].isPlaying()) {
//     debug::println((String) "Channel " + channel +
//                    " is already playing, but is requested to play " + fileName);
//   }
//   playSdWav[channel].play(fileName);
//   PrintFileInfo(channel, fileName);
// }

// size_t GetIdleChannel() {
//   const static size_t first_channel = 3;

//   // Find first available channel, starting with first_channel
//   for (size_t channel = first_channel; channel < kChannelCount; ++channel) {
//     if (!playSdWav[channel].isPlaying()) {
//       return channel;
//     }
//   }

//   // Default to first_channel if they're all already playing something
//   debug::println("OVERWRITE==OVERWRITE==OVERWRITE (all channels playing)");
//   return first_channel;
// }

// void PlayWav(const char* fileName) {
//   const size_t channel = GetIdleChannel();
//   StartChannel(channel, fileName);
// }

// //=============================================================================//
// // SETUP AND LOOP
// void setup() {
//   Serial.begin(115200);
//   audio::InitAudio();

//   //   mixMaster.gain(0, 0.5);
//   //   mixMaster.gain(1, 0.5);
//   //   mixer1.gain(0, mixerGain);
//   //   mixer1.gain(1, mixerGain);
//   //   mixer1.gain(2, mixerGain);
//   //   mixer1.gain(3, mixerGain);
//   //   mixer2.gain(0, mixerGain);
//   //   mixer2.gain(1, mixerGain);
//   //   mixer2.gain(2, mixerGain);
//   //   mixer2.gain(3, mixerGain);
//   //   effectMixer.gain(0, mixerGain);
//   //   effectMixer.gain(1, mixerGain);
//   //   effectMixer.gain(2, mixerGain);
//   //   effectMixer.gain(3, mixerGain);
//   //   bgMixer.gain(0, mixerGain);
//   //   bgMixer.gain(1, mixerGain);
//   //   bgMixer.gain(2, mixerGain);
//   //   bgMixer.gain(3, mixerGain);

//   PlayWav("FUEL50.WAV");
//   delay(800);
//   PlayWav("FUEL100.WAV");
//   delay(1000);

//   debug::println("starting the loop");
// }

// void channelChecker(char* message) {
//   char channelChar = message[0];
//   size_t channelNum = channelChar - '0';
//   if (channelNum >= 0 && channelNum < kChannelCount) {
//     const bool isStart = (message[1] == '1');
//     if (isStart) {
//       message++;
//       message++;
//       StartChannel(channelNum, message);
//     } else {
//       StopChannel(channelNum);
//     }
//   } else {
//     PlayWav(message);
//   }
// }

// void loop() {
//   for (size_t i = 0; i < 2; i++) {
//     serialReceiver[i].recvWithStartEndMarkers();
//     while (serialReceiver[i].hasMessages()) {
//       char output[32];
//       serialReceiver[i].getNextMessage(output);
//       debug::println((String) "playing from serial[" + i + "]: " + output);
//       channelChecker(output);
//     }
//   }
// }
