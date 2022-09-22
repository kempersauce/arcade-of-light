#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

#include <string>
#include <vector>

#include "audio/constants.h"     // for SynthAudioMessage
#include "audio/synthy.h"        // for Synth
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for reciever
// #include "pins/pin_setup.h"

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::_synthy;

Synthy synthy;

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
  synthy.InitSynth();

  Debug("synth maked");
}

void loop() {
  receiver.ReceiveMessages();
  SynthAudioMessage msg;

  if (receiver.GetNextMessage(msg)) {
    auto& channel = waveforms[msg.channel];

    // RIGHT BUTTON
    if (msg.channel == 0) {
      if (msg.action == kChannelActionPlay) {
        Debug("Play channel " + msg.channel);
        waveforms[2].envelope.noteOn();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        waveforms[2].envelope.noteOff();
      }
    }
    // LEFT BUTTON
    if (msg.channel == 1) {
      if (msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        waveforms[3].envelope.noteOn();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        waveforms[3].envelope.noteOff();
      }
    }
    // UP BUTTON
    if (msg.channel == 2) {
      if (msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        waveforms[4].pitchBendStart(waveforms[4].frequency, true);
        // channel.envelope.noteOn();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        waveforms[4].pitchBendStop();
      }
    }
    // DOWN BUTTON
    if (msg.channel == 3) {
      if (msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        waveforms[4].pitchBendStart(waveforms[4].frequency, false);
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        waveforms[4].pitchBendStop();
      }
    }
    // A BUTTON
    if (msg.channel == 4) {
      if (msg.action == kChannelActionPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        float note = synthy.playSequence();
        Debug(note);
        waveforms[4].setFrequency(note);
        waveforms[4].adjustPitchBend(note);
        waveforms[4].envelope.noteOn();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        waveforms[4].envelope.noteOff();
      }
    }
    // B BUTTON
    if (msg.channel == 5) {
      if (msg.action == kChannelActionPlay) {
        // What it do if pressing button
        float note = synthy.reverseSequence();
        waveforms[4].setFrequency(note);
        Debug(note);
        Debug("Play channel " + msg.channel);
        waveforms[4].adjustPitchBend(note);
        waveforms[4].envelope.noteOn();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        waveforms[4].envelope.noteOff();
      }
    }
  }

  if (waveforms[4].bendStarted) {
    waveforms[4].pitchBend();
  }
}