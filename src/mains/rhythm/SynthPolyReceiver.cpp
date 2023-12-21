#include <Audio.h>

#include "audio/constants.h"     // for SynthAudioMessage
#include "audio/sounds.h"        // for audio::Init
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
  audio::Init(false);

  Debug("making synth");
  synth.InitSynth();

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
        synth.actionRight();
      } else {
        // What it do when releast button
        synth.stopRight();
        Debug("Stop channel %d", msg.channel);
        // guitar.stopString1();
      }
    }
    // LEFT BUTTON
    if (msg.channel == kLeftChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel %d", msg.channel);
        synth.actionLeft();
      } else {
        // What it do when releast button
        synth.stopLeft();
        Debug("Stop channel %d", msg.channel);
        // guitar.stopString2();
      }
    }
    // UP BUTTON
    if (msg.channel == kUpChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel %d", msg.channel);
        synth.actionUp();
        // channel.envelope.noteOn();
      } else {
        // What it do when releast button
        synth.stopLeft();
        Debug("Stop channel %d", msg.channel);
        // guitar.stopString3();
      }
    }
    // DOWN BUTTON
    if (msg.channel == kDownChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel %d", msg.channel);
        synth.actionDown();
      } else {
        // What it do when releast button
        synth.stopDown();
        Debug("Stop channel %d", msg.channel);
        // guitar.stopString4();
      }
    }
    // A BUTTON
    if (msg.channel == kAChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel %d", msg.channel);
        synth.actionA();
      } else {
        // What it do when releast button
        Debug("Stop channel %d", msg.channel);
        synth.stopA();
        // guitar.stopString5();
      }
    }
    // B BUTTON
    if (msg.channel == kBChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel %d", msg.channel);
        synth.actionB();
      } else {
        // What it do when releast button
        Debug("Stop channel %d", msg.channel);
        synth.stopArp();
        // guitar.stopString6();
      }
    }
  }

  if (synth.arpOn) {
    synth.playArp();
  }
}
