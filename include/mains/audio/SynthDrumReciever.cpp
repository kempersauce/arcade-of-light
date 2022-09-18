#pragma once

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <synth_simple_drum.h>

#include "audio/constants.h"     // for SynthAudioMessage
// #include "audio/synthy.h"        // for Synth
#include "audio/drum_synthy.h"
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for reciever

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::_synthy;

DrumSynthy synthy;

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

  Debug("making synth");
  synthy.InitDrumSynth();

  Debug("synth maked");
}

void loop() {
  receiver.ReceiveMessages();
  SynthAudioMessage msg;

  if (receiver.GetNextMessage(msg)) {
    // auto& channel = waveforms[msg.channel];

    // RIGHT BUTTON
    if(msg.channel == 0) {
      if(msg.action == kChannelActionPlay) {
        Debug("Play channel " + msg.channel);
        synthy.playDrum1();
      } 
    }
    // LEFT BUTTON
    if(msg.channel == 1) {
      if(msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        synthy.playDrum1();
      } 
    }
    // UP BUTTON
    if(msg.channel == 2) {
      if(msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        synthy.playDrum2();
      }
    }
    // DOWN BUTTON
    if(msg.channel == 3) {
      if(msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        synthy.playDrum2();
      } 
    }
    // A BUTTON
    if(msg.channel == 4) {
      if(msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        synthy.playDrum3();
      } 
    }
    // B BUTTON
    if(msg.channel == 5) {
      if(msg.action == kChannelActionPlay) {
        // What it do if pressing button
        synthy.playDrum4();
      }
    }
  }
}
