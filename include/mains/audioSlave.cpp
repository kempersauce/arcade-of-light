#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

#include <string>
#include <vector>

#include "audio/slave_driver.h"  // for SlaveDriver
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for EZReceiver

using namespace kss;
using namespace kss::audio;

SlaveDriver slaveDriver;

void ProcessMessage(const AudioMessage& message) {
  auto& channel = slaveDriver.GetChannel(message.channel_selector);
  switch (message.action_selector) {
    case kChannelActionPlay:
      channel.Play(message.filename);
      break;

    case kChannelActionRepeat:
      channel.Repeat(message.filename);
      break;

    case kChannelActionStop:
      channel.Stop();
      break;

    default:
      Debug("Error: Unrecognized channel action '" + message.action_selector +
            "' (message: \"" + message.filename + "\")");
      break;
  }
}

serial::EZReceiver<AudioMessage> receiver{&Serial1};

//=============================================================================//
// SETUP AND LOOP
void setup() {
  Debug_init();

  // Fire up the boombox
  InitAudio();

  auto& channel = slaveDriver.PlayWav("FUEL50.WAV");
  while (channel.IsPlaying()) {
    delay(1);
  }

  channel.Play("FUEL100.WAV");

  Debug("starting the loop");
}

void loop() {
  slaveDriver.UpdateAll();
  while (receiver.ReceiveMessages()) {
  }
  AudioMessage msg;
  while (receiver.GetNextMessage(msg)) {
    ProcessMessage(msg);
  }
}
