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

  Debug("making synth");
  synthy.InitSynth();

  Debug("synth maked");
}

void loop() {
  receiver.ReceiveMessages();
  SynthAudioMessage msg;
  if (receiver.GetNextMessage(msg)) {
    auto& channel = waveforms[msg.channel];
    AudioNoInterrupts();
    if (msg.action == kChannelActionPlay) {
      Debug("Play channel " + msg.channel);
      channel.envelope.noteOn();
    } else {
      Debug("Stop channel " + msg.channel);
      channel.envelope.noteOff();
    }
    AudioInterrupts();
    audioDebug();
  }
}
