#include <Wire.h>

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
  auto& channel = wav_manager.GetChannel(message.channel_selector);
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

    default:
      Debug("Error: Unrecognized channel action '" + message.action_selector +
            "' (message: \"" + message.filename + "\")");
      break;
  }
}

serial::EZReceiver<WavAudioMessage> receiver{&Serial1};

engines::FrameRate framerate;

//=============================================================================//
// SETUP AND LOOP
void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  // Fire up the boombox
  audio::Init();

  auto& channel = wav_manager.PlayWav("FUEL50.WAV");
  while (channel.IsPlaying()) {
    time::SetLoopTime();
  }

  channel.Play("FUEL100.WAV");

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
