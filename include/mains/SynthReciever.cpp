#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

#include <string>
#include <vector>

#include "audio/synthy.h"        // for Synth
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for reciever

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::_synthy;

Synthy synthy;

// TODO: Rewrite this to recieve new synth sender messages
struct message {
  uint8_t action;
};
serial::EZReceiver<message> receiver(&Serial1);

//=============================================================================//
// SETUP AND LOOP
void setup() {
  Debug_init();

  Debug("making synth");
  synthy.InitSynth();

  Debug("synth maked");
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
  if (receiver.GetNextMessage(receivedMessage)) {
    if (receivedMessage.action == kChannelActionPlay) {
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
  Debug("starting the loop");
  synthy.Play();
}
