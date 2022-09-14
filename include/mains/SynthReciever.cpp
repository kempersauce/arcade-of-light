#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

#include <string>
#include <vector>

// #include "audio/slave_driver.h"    // for SlaveDriver
#include "serial/debug.h"          // for debug::*
#include "audio/synthy.h"           // for Synth
#include "serial/ez_receiver.h"    // for reciever

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::_synthy;

// SlaveDriver slaveDriver;

Synthy synthy;

// TODO: Rewrite this to recieve new synth sender messages
struct message{uint8_t action;};
serial::EZReceiver <message> receiver(&Serial1);

// serial::ReceiverBank receivers{ProcessMessage, serials};

//=============================================================================//
// SETUP AND LOOP
void setup() {
  debug::Init();

  
  
  debug::println("making synth");
  synthy.InitSynth();


  debug::println("synth maked");
  synthy.wave1Amplitude = 0;
  synthy.wave2Amplitude = 0;
  synthy.wave3Amplitude = 0;
  synthy.wave4Amplitude = 0;
  synthy.wave5Amplitude = 0;
  synthy.wave6Amplitude = 0;
}

void loop() {
  receiver.ReceiveMessages();
  message receivedMessage;
  if(receiver.GetNextMessage(receivedMessage)) {
    if(receivedMessage.action == kChannelActionPlay) {
      synthy.wave1Amplitude = 1.0;
      synthy.wave2Amplitude = 1.0;
      synthy.wave3Amplitude = 1.0;
      synthy.wave4Amplitude = 1.0;
      synthy.wave5Amplitude = 1.0;
      synthy.wave6Amplitude = 1.0;
    } else {
      synthy.wave1Amplitude = 0;
      synthy.wave2Amplitude = 0;
      synthy.wave3Amplitude = 0;
      synthy.wave4Amplitude = 0;
      synthy.wave5Amplitude = 0;
      synthy.wave6Amplitude = 0;
    }
  }
  debug::println("starting the loop");
  synthy.Play();
//   receivers.ReadAll();
}
