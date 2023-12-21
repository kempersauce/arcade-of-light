#include <Wire.h>

#include "audio/channel.h"       // for Channel
#include "audio/sounds.h"        // for audio::Init
#include "audio/wav_manager.h"   // for WavAudioManager
#include "engines/framerate.h"   // for Framerate
#include "pins/pin_setup.h"      // for pins::Init
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for EZReceiver
#include "time/now.h"            // for time::*

using namespace kss;
using namespace kss::audio;

WavAudioManager wav_manager;

void ProcessMessage(const WavAudioMessage& message) {
  Channel& channel = wav_manager.GetChannel(message.channel_selector);
  switch (message.action_selector) {
    case kActionChannelPlay:
      channel.Play(message.filename);
      break;

    case kActionChannelRepeat:
      channel.Repeat(message.filename);
      break;

    case kActionChannelStop:
      channel.Stop();
      break;

    case kActionChannelGain:
      channel.SetGain(message.gain);
      break;

    default:
      Debug("Error: Unrecognized channel action '%c' (message: \"%s\")",
            message.action_selector, message.filename);
      break;
  }
}

serial::EZReceiver<WavAudioMessage> receiver{&Serial1};

engines::FrameRate framerate;

inline void StartChannel(uint8_t channel_index, char* filename, float gain) {
  Channel& channel = wav_manager.GetChannelByIndex(channel_index);
  channel.SetGainCoefficient(gain);
  channel.SetGain(1);
  channel.Repeat(filename);
}

//=============================================================================//
// SETUP AND LOOP
void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  // Fire up the boombox
  audio::Init();

  time::SetLoopTime();
  Channel& channel = wav_manager.PlayWav("FUEL50.WAV");
  while (channel.IsPlaying()) {
    time::SetLoopTime();
  }

  uint8_t channel_index = 0;
  if (!pins::ReadDip(0)) {
    StartChannel(channel_index++, "BEE.WAV", 0.25f);
    StartChannel(channel_index++, "FROGGY.WAV", 0.5f);
    StartChannel(channel_index++, "OWL.WAV", 0.6f);
    StartChannel(channel_index++, "NATPAD.WAV", 0.5f);
    StartChannel(channel_index++, "STREAM.WAV", 0.5f);
    StartChannel(channel_index++, "THUNDER.WAV", 0.45f);
  } else {
    StartChannel(channel_index++, "KILLDEER.WAV", 0.5f);
    StartChannel(channel_index++, "KATYDID.WAV", 0.5f);
    // StartChannel(channel_index++, "OWL.WAV", 0.6f);
    // StartChannel(channel_index++, "NATPAD.WAV", 0.5f);
    // StartChannel(channel_index++, "STREAM.WAV", 0.5f);
    // StartChannel(channel_index++, "THUNDER.WAV", 0.5f);
  }

  Debug("starting the loop");
}

void loop() {
  time::SetLoopTime();
  wav_manager.UpdateAll();
  while (receiver.ReceiveMessages()) {
  }
  WavAudioMessage msg;
  while (receiver.GetNextMessage(msg)) {
    ProcessMessage(msg);
  }
  //   framerate.PrintFrameRate();
}
