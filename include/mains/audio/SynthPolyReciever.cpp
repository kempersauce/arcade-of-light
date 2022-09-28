#include <Audio.h>

#include "audio/constants.h"     // for SynthAudioMessage
#include "audio/sounds.h"        // for InitAudio
#include "audio/synthy_poly.h"   // for Synth
#include "pins/pin_setup.h"      // for pins::Init
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for reciever

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::_synthy_poly;

SynthyPoly synth;

serial::EZReceiver<SynthAudioMessage> receiver{&Serial1};

//=============================================================================//
// SETUP AND LOOP
void setup() {
  Debug_init();
  pins::Init();
  audio::InitAudio();

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
    if (msg.channel == kRightChannelNum) {
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
    if (msg.channel == kLeftChannelNum) {
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
    if (msg.channel == kUpChannelNum) {
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
    if (msg.channel == kDownChannelNum) {
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
    if (msg.channel == kAChannelNum) {
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
    if (msg.channel == kBChannelNum) {
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
