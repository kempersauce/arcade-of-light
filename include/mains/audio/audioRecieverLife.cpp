#include <Wire.h>

#include "audio/sounds.h"        // for audio::Init
#include "audio/wav_manager_life.h"   // for WavAudioManagerLife
#include "engines/framerate.h"   // for Framerate
#include "pins/pin_setup.h"      // for pins::Init
#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for EZReceiver
#include "time/now.h"            // for time::*

using namespace kss;
using namespace kss::audio;

WavAudioManagerLife wav_manager;

void ProcessMessage(const WavAudioMessage& message) {
  char channel = size_t(message[0]);
  float level = float(message[1,2] / 100);
  wav_manager.AdjustGain(channel, level);
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

  wav_manager.Setup();

  Debug("starting the loop");
}

serial::EZReceiver<WavAudioMessage> receiver{&Serial1};

engines::FrameRate framerate;

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
