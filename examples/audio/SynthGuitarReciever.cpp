#include <Arduino.h>
#include <Audio.h>
#include <SPI.h>
#include <Wire.h>

#include "audio/constants.h"      // for SynthAudioMessage
#include "audio/guitar_synthy.h"  // for Synth
#include "audio/sounds.h"         // for audio::Init
#include "pins/pin_setup.h"       // pins::Init
#include "serial/debug.h"         // for Debug
#include "serial/ez_receiver.h"   // for reciever

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::_guitar;

GuitarSynthy guitar;

serial::EZReceiver<SynthAudioMessage> receiver{&Serial1};

//=============================================================================//
// SETUP AND LOOP
void setup() {
  Debug_init();
  pins::Init();
  audio::Init(false);

  Debug("making synth");
  guitar.InitGuitarSynth();

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
        Debug("Play channel " + msg.channel);
        guitar.actionRight();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        // guitar.stopString1();
      }
    }
    // LEFT BUTTON
    if (msg.channel == kLeftChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        guitar.actionLeft();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        // guitar.stopString2();
      }
    }
    // UP BUTTON
    if (msg.channel == kUpChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        guitar.actionUp();
        // channel.envelope.noteOn();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        // guitar.stopString3();
      }
    }
    // DOWN BUTTON
    if (msg.channel == kDownChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        guitar.actionDown();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        // guitar.stopString4();
      }
    }
    // A BUTTON
    if (msg.channel == kAChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        guitar.actionA();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        // guitar.stopString5();
      }
    }
    // B BUTTON
    if (msg.channel == kBChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        guitar.actionB();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        // guitar.stopString6();
      }
    }
  }
}
