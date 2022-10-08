#include <Audio.h>

#include "audio/constants.h"     // for SynthAudioMessage
#include "audio/sounds.h"        // for audio::Init
#include "audio/synthy.h"        // for Synth
#include "pins/pin_setup.h"      // for pins::Init
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for reciever

using namespace kss;
using namespace kss::audio;
using namespace kss::audio::_synthy;

Synthy synthy;

serial::EZReceiver<SynthAudioMessage> receiver{&Serial1};

//=============================================================================//
// SETUP AND LOOP
void setup() {
  Debug_init();
  pins::Init();
  audio::Init(false);

  Debug("making synth");
  synthy.InitSynth();

  Debug("synth maked");
}

void loop() {
  receiver.ReceiveMessages();
  SynthAudioMessage msg;

  while (receiver.GetNextMessage(msg)) {
    auto& channel = waveforms[msg.channel];

    // RIGHT BUTTON
    if (msg.channel == kRightChannelNum) {
      if (msg.action == kActionChannelPlay) {
        Debug("Play channel " + msg.channel);
        waveforms[4].filterSweepStart(true);
        if (!synthy.sequencerOn) {
          waveforms[4].envelope.noteOn();
        }
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        waveforms[4].filterSweepStop();
        if (!synthy.sequencerOn) {
          waveforms[4].envelope.noteOff();
        }
      }
    }
    // LEFT BUTTON
    if (msg.channel == kLeftChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        waveforms[4].filterSweepStart(false);
        if (!synthy.sequencerOn) {
          waveforms[4].envelope.noteOn();
        }
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        waveforms[4].filterSweepStop();
        if (!synthy.sequencerOn) {
          waveforms[4].envelope.noteOff();
        }
      }
    }
    // UP BUTTON
    if (msg.channel == kUpChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        waveforms[4].pitchBendStart(waveforms[4].frequency, true);
        waveforms[4].envelope.noteOn();
        // channel.envelope.noteOn();
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        waveforms[4].pitchBendStop();
        if (!synthy.sequencerOn) {
          waveforms[4].envelope.noteOff();
        }
      }
    }
    // DOWN BUTTON
    if (msg.channel == kDownChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        waveforms[4].pitchBendStart(waveforms[4].frequency, false);
        waveforms[4].envelope.noteOn();

      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        waveforms[4].pitchBendStop();
        if (!synthy.sequencerOn) {
          waveforms[4].envelope.noteOff();
        }
      }
    }
    // A BUTTON
    if (msg.channel == kAChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        Debug("Play channel " + msg.channel);
        float note = synthy.playSequence();
        waveforms[4].setFrequency(note);
        waveforms[4].adjustPitchBend(note);
        waveforms[4].envelope.noteOn();
        synthy.sequencerOn = true;
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        waveforms[4].envelope.noteOff();
        synthy.sequencerOn = false;
      }
    }
    // B BUTTON
    if (msg.channel == kBChannelNum) {
      if (msg.action == kActionChannelPlay) {
        // What it do if pressing button
        float note = synthy.reverseSequence();
        waveforms[4].setFrequency(note);
        Debug("Play channel " + msg.channel);
        waveforms[4].adjustPitchBend(note);
        waveforms[4].envelope.noteOn();
        synthy.sequencerOn = true;
      } else {
        // What it do when releast button
        Debug("Stop channel " + msg.channel);
        waveforms[4].envelope.noteOff();
        synthy.sequencerOn = false;
      }
    }
  }

  if (waveforms[4].bendStarted) {
    waveforms[4].pitchBend();
  }
  if (waveforms[4].sweepStarted) {
    waveforms[4].filterSweep();
  }
}
