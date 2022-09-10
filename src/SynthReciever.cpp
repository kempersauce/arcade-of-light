#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

#include <string>
#include <vector>

#include "audio/slave_driver.h"    // for SlaveDriver
#include "serial/debug.h"          // for debug::*
#include "serial/receiver_bank.h"  // for ReceiverBank
#include "audio/synthy.h"           // for Synth

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::_synthy;

// SlaveDriver slaveDriver;

Synthy synthy;

// TODO: Rewrite this to recieve new synth sender messages
// void ProcessMessage(const char* message) {
//   const char startChar = "";
//   const char stopChar = "";
//   const char marker = message[0];
//   const char action = message[1];
//   const char* fileName = message + 2;
//   auto& channel = slaveDriver.GetChannel(marker);
//   switch (action) {
//     case kChannelActionPlay:
//       channel.Play(fileName);
//       break;

//     case kChannelActionStop:
//       channel.Stop();
//       break;

//     default:
//       debug::println((String)"Error: Unrecognized channel action \"" + action +
//                      "\" (message: \"" + message + "\")");
//       break;
//   }
// }

// // Serials we listen on
// const std::vector<HardwareSerial*> serials{
//     &Serial1,  // OK
//     //&Serial2,  // TX2 & RX2 are used by audioshield
//     //&Serial3,  // AudioShield uses RX3 for volume control
//     &Serial4,  // OK
//     //&Serial5,  // TX5 & RX5 are used by audioshield
//     &Serial6,  // OK
//     &Serial7   // OK
// };

// serial::ReceiverBank receivers{ProcessMessage, serials};

//=============================================================================//
// SETUP AND LOOP
void setup() {
  debug::Init();

  // Fire up the boombox
  InitAudio();

    // mixMaster.gain(0, 0.5);
    // mixMaster.gain(1, 0.5);
    // mixer1.gain(0, mixerGain);
    // mixer1.gain(1, mixerGain);
    // mixer1.gain(2, mixerGain);
    // mixer1.gain(3, mixerGain);
    // mixer2.gain(0, mixerGain);
    // mixer2.gain(1, mixerGain);
    // mixer2.gain(2, mixerGain);
    // mixer2.gain(3, mixerGain);
    // effectMixer.gain(0, mixerGain);
    // effectMixer.gain(1, mixerGain);
    // effectMixer.gain(2, mixerGain);
    // effectMixer.gain(3, mixerGain);
    // bgMixer.gain(0, mixerGain);
    // bgMixer.gain(1, mixerGain);
    // bgMixer.gain(2, mixerGain);
    // bgMixer.gain(3, mixerGain);

//   auto& channel = slaveDriver.PlayWav("FUEL50.WAV");
//   while (channel.IsPlaying()) {
    // delay(1);

//   }
  
  debug::println("making synth");
  synthy.InitSynth();


  debug::println("synth maked");
}

void loop() {
  delay(2000);
  debug::println("starting the loop");
  synthy.Play();
//   receivers.ReadAll();
}
