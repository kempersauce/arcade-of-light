#include <Arduino.h>
#include <Audio.h>
#include <HardwareSerial.h>
#include <SPI.h>
#include <Wire.h>

#include "audio/constants.h"     // for SynthAudioMessage
#include "audio/drum_synthy.h"   // for DrumSynthy
#include "audio/sounds.h"        // for audio::Init
#include "pins/pin_setup.h"      // for pins::Init
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for reciever

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::_synthy;

DrumSynthy synthy;

serial::EZReceiver<SynthAudioMessage> receiver{&Serial1};

//=============================================================================//
// SETUP AND LOOP
void setup() {
  Debug_init();
  pins::Init();
  audio::Init(false);

  Debug("making synth");
  synthy.InitDrumSynth();

  Debug("synth maked");
}

void loop() {
  receiver.ReceiveMessages();
  SynthAudioMessage msg;

  while (receiver.GetNextMessage(msg)) {
    // auto& channel = waveforms[msg.channel];

    // RIGHT BUTTON
    if (msg.channel == kRightChannelNum) {
      if (msg.action == kActionChannelPlay) {
        Debug("Play channel %d", msg.channel);
        synthy.playDrum1();
      }
    }
    // LEFT BUTTON
    if (msg.channel == kLeftChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel %d", msg.channel);
        synthy.playDrum1();
      }
    }
    // UP BUTTON
    if (msg.channel == kUpChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel %d", msg.channel);
        synthy.playDrum2();
      }
    }
    // DOWN BUTTON
    if (msg.channel == kDownChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel %d", msg.channel);
        synthy.playDrum2();
      }
    }
    // A BUTTON
    if (msg.channel == kAChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel %d", msg.channel);
        synthy.playDrum3();
      }
    }
    // B BUTTON
    if (msg.channel == kBChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel %d", msg.channel);
        synthy.playDrum4();
      }
    }
  }
}
