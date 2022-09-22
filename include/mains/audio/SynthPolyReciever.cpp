#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

#include <string>
#include <vector>

#include "audio/constants.h"     // for SynthAudioMessage
#include "audio/synthy_poly.h"   // for Synth
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for reciever
// #include "pins/pin_setup.h"

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::_synthy_poly;

SynthyPoly synth;

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
  synth.InitSynth();

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
        synth.actionRight();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        // guitar.stopString1();
      }
    }
    // LEFT BUTTON
    if (msg.channel == 1) {
      if (msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        synth.actionLeft();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        // guitar.stopString2();
      }
    }
    // UP BUTTON
    if (msg.channel == 2) {
      if (msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        synth.actionUp();
        // channel.envelope.noteOn();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        // guitar.stopString3();
      }
    }
    // DOWN BUTTON
    if (msg.channel == 3) {
      if (msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        synth.actionDown();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        // guitar.stopString4();
      }
    }
    // A BUTTON
    if (msg.channel == 4) {
      if (msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        synth.actionA();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        synth.stopA();
        // guitar.stopString5();
      }
    }
    // B BUTTON
    if (msg.channel == 5) {
      if (msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        synth.actionB();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        synth.stopArp();
        // guitar.stopString6();
      }
    }
  }
  if (synth.arpOn) {
    synth.playArp();
  }
}
