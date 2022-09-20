#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

#include <string>
#include <vector>

#include "audio/constants.h"     // for SynthAudioMessage
#include "audio/synthy_moog.h"        // for Synth
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for reciever
// #include "pins/pin_setup.h"

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::moog;

MoogSynthy synthy;

serial::EZReceiver<SynthAudioMessage> receiver(&Serial1);

const void audioDebug() {
  Debug("Proc=" + AudioProcessorUsage() + " (max=" + AudioProcessorUsageMax() +
        "), Mem=" + AudioMemoryUsage() + " (max=" + AudioMemoryUsageMax() +
        ")");
}

//=============================================================================//
// SETUP AND LOOP
void setup() {
  Debug_init();
  // pins::Init();

  Debug("making synth");
  synthy.InitMoogSynthy();

  Debug("synth maked");
}


void loop() {
  receiver.ReceiveMessages();
  SynthAudioMessage msg;

  if (receiver.GetNextMessage(msg)) {
    // auto& channel = waveforms[msg.channel];

    // RIGHT BUTTON
    if (msg.channel == 0) {
      if (msg.action == kChannelActionPlay) {
        Debug("Play channel " + msg.channel);
        synthy.actionRight();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        synthy.stopNote();
      }
    }
    // LEFT BUTTON
    if (msg.channel == 1) {
      if (msg.action == kChannelActionPlay) {
        Debug("Play channel " + msg.channel);
        synthy.actionLeft();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        synthy.stopNote();
      }
    }
    // UP BUTTON
    if (msg.channel == 2) {
      if (msg.action == kChannelActionPlay) {
        Debug("Play channel " + msg.channel);
        synthy.actionUp();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        synthy.stopNote();
      }
    }
    // DOWN BUTTON
    if (msg.channel == 3) {
      if (msg.action == kChannelActionPlay) {
        Debug("Play channel " + msg.channel);
        synthy.actionDown();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        synthy.stopNote();
      }
    }
    // A BUTTON
    if (msg.channel == 4) {
      if (msg.action == kChannelActionPlay) {
        Debug("Play channel " + msg.channel);
        synthy.actionA();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        synthy.stopNote();
      }
    }
    // B BUTTON
    if (msg.channel == 5) {
      if (msg.action == kChannelActionPlay) {
        Debug("Play channel " + msg.channel);
        synthy.actionB();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        synthy.stopNote();
      }
    }
  }

}
