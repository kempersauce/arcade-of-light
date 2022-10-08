#include <Audio.h>
#include <HardwareSerial.h>

#include "audio/constants.h"     // for SynthAudioMessage
#include "audio/drum_wav.h"      // for DrumWav
#include "audio/sounds.h"        // for audio::Init
#include "pins/pin_setup.h"      // for pins::Init
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for reciever

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::drumWav;

DrumWav drums;

serial::EZReceiver<SynthAudioMessage> receiver(&Serial1);

//=============================================================================//
// SETUP AND LOOP
void setup() {
  Debug_init();
  pins::Init();
  audio::Init();
  drums.drumSetup();

  Debug("drums maked");
}

void loop() {
  receiver.ReceiveMessages();
  SynthAudioMessage msg;

  while (receiver.GetNextMessage(msg)) {
    // Click track action
    if (msg.action == kActionClickTrack) {
      Debug("Click track received for beat " + msg.channel);
      // TODO figure out what to do with this click track
      if (msg.channel == 0) {
        drums.playDrum6();
      } else {
        drums.playDrum4();
      }
      continue;
    }

    // RIGHT BUTTON
    if (msg.channel == kRightChannelNum) {
      if (msg.action == kActionChannelPlay) {
        Debug("Play channel " + msg.channel);
        drums.playDrum1();
      }
    }
    // LEFT BUTTON
    if (msg.channel == kLeftChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        drums.playDrum2();
      } else {
        drums.stopDrum2();
      }
    }
    // UP BUTTON
    if (msg.channel == kUpChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        drums.playDrum3();
      }
    }
    // DOWN BUTTON
    if (msg.channel == kDownChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        drums.playDrum4();
      }
    }
    // A BUTTON
    if (msg.channel == kAChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        drums.playDrum5();
      }
    }
    // B BUTTON
    if (msg.channel == kBChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        drums.playDrum6();
        // drums.triggerGlitch();
      }
    }
  }
}
