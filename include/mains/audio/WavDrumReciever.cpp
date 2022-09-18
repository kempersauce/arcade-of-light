#pragma once

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


#include "audio/constants.h"     // for SynthAudioMessage
#include "audio/drum_wav.h"
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for reciever
#include "PinSetup.h"

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::drumWav;

DrumWav drums;

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
  pins::Init();

  Debug("making drums");
  drums.InitDrums();

  Debug("drums maked");
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
        drums.playDrum1();
      } 
    }
    // LEFT BUTTON
    if(msg.channel == 1) {
      if(msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        drums.playDrum2();
      } else {
        drums.stopDrum2();
      }
    }
    // UP BUTTON
    if(msg.channel == 2) {
      if(msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        drums.playDrum3();
      }
    }
    // DOWN BUTTON
    if(msg.channel == 3) {
      if(msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        drums.playDrum4();
      } 
    }
    // A BUTTON
    if(msg.channel == 4) {
      if(msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        drums.playDrum5();
      } 
    }
    // B BUTTON
    if(msg.channel == 5) {
      if(msg.action == kChannelActionPlay) {
        // What it do if pressing button
        drums.playDrum6();
      }
    }
  }
}
