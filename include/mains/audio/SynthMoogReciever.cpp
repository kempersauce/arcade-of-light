#include <Audio.h>

#include "audio/constants.h"     // for SynthAudioMessage
#include "audio/sounds.h"        // for InitAudio
#include "audio/synthy_moog.h"   // for Synth
#include "pins/pin_setup.h"      // for pins::Init
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for reciever

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::moog;

MoogSynthy synthy;

serial::EZReceiver<SynthAudioMessage> receiver{&Serial1};

//=============================================================================//
// SETUP AND LOOP
void setup() {
  Debug_init();
  pins::Init();
  audio::InitAudio();

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
    if (msg.channel == kRightChannelNum) {
      if (msg.action == kChannelActionPlay) {
        Debug("Play channel " + msg.channel);
        synthy.actionRight();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        synthy.stopJoystick();
      }
    }
    // LEFT BUTTON
    if (msg.channel == kLeftChannelNum) {
      if (msg.action == kChannelActionPlay) {
        Debug("Play channel " + msg.channel);
        synthy.actionLeft();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        synthy.stopJoystick();
      }
    }
    // UP BUTTON
    if (msg.channel == kUpChannelNum) {
      if (msg.action == kChannelActionPlay) {
        Debug("Play channel " + msg.channel);
        synthy.actionUp();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        synthy.stopJoystick();
      }
    }
    // DOWN BUTTON
    if (msg.channel == kDownChannelNum) {
      if (msg.action == kChannelActionPlay) {
        Debug("Play channel " + msg.channel);
        synthy.actionDown();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        synthy.stopJoystick();
      }
    }
    // A BUTTON
    if (msg.channel == kAChannelNum) {
      if (msg.action == kChannelActionPlay) {
        Debug("Play channel " + msg.channel);
        synthy.actionA();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        synthy.stopA();
      }
    }
    // B BUTTON
    if (msg.channel == kBChannelNum) {
      if (msg.action == kChannelActionPlay) {
        Debug("Play channel " + msg.channel);
        synthy.actionB();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        synthy.stopB();
      }
    }
  }
}
