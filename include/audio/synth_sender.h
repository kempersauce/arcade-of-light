#pragma once

#include <HardwareSerial.h>  // for HardwareSerial

#include "audio/constants.h"  // for k*
#include "controls/button.h"
#include "serial/debug.h"           // for Debug
#include "serial/ez_transmitter.h"  // for Transmitter

namespace kss {
namespace audio {

class SynthSender {
  // Button time
  controls::Button* btns[6];

  serial::EZTransmitter<SynthAudioMessage> transmitter;

 public:
  // Constructor: starts serial connection to audioSlave
  SynthSender(controls::Button* up, controls::Button* down,
              controls::Button* left, controls::Button* right,
              controls::Button* a, controls::Button* b,
              HardwareSerial* serial = &Serial1)
      : btns{up, down, left, right, a, b}, transmitter{serial} {}

  const void Send(uint8_t channel, uint8_t action) {
    SynthAudioMessage msg;
    msg.action = action;
    msg.channel = channel;
    transmitter.Send(msg);
  }

  // prepare input started message for synth
  const void StartInput(uint8_t channel) {
    Send(channel, kChannelActionPlay);
    Debug("Sent <PLay> on channel " + channel);
  }

  // prepare input stop message for synth
  const void StopInput(uint8_t channel) {
    Send(channel, kChannelActionStop);
    Debug("Sent <STop> on channel " + channel);
  }

  // checks if any buttons have changed state
  const void checkButtonChange() {
    for (size_t i = 0; i < 6; ++i) {
      if (btns[i]->IsDepressing()) {
        StartInput(i);
      }
      if (btns[i]->IsReleasing()) {
        StopInput(i);
      }
    }
  }
};

}  // namespace audio
}  // namespace kss
