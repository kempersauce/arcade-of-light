#include <Wire.h>

#include "audio/sounds.h"        // for audio::Init
#include "audio/wav_manager.h"   // for WavAudioManagerLife
#include "engines/framerate.h"   // for Framerate
#include "pins/pin_setup.h"      // for pins::Init
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for EZReceiver
#include "time/now.h"            // for time::*

using namespace kss;
using namespace kss::audio;

WavAudioManager wav_manager;

void ProcessMessage(const WavAudioMessage& message) {
  const float level = message.gain / 100.0f;
  wav_manager.GetChannel(message.channel_selector).SetGain(level);
}

serial::EZReceiver<WavAudioMessage> receiver{&Serial1};

engines::FrameRate framerate;

void setup() {
  Debug_init();
  pins::Init();
  time::Init();

  // Fire up the boombox
  audio::Init();

  Debug("starting the loop");
}

void loop() {
  time::SetLoopTime();
  while (receiver.ReceiveMessages()) {
  }
  WavAudioMessage msg;
  while (receiver.GetNextMessage(msg)) {
    ProcessMessage(msg);
  }
  //   framerate.PrintFrameRate();
}
