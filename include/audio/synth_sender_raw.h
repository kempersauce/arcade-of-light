#pragma once

#include <HardwareSerial.h>  // for HardwareSerial

#include "audio/constants.h"        // for k*
#include "serial/debug.h"           // for Debug
#include "serial/ez_transmitter.h"  // for Transmitter

namespace kss {
namespace audio {

class SynthSenderRaw {
  serial::EZTransmitter<SynthAudioMessage> transmitter;

  void Send(uint8_t channel, uint8_t action) {
    SynthAudioMessage msg;
    msg.action = action;
    msg.channel = channel;
    transmitter.Send(msg);
  }

 public:
  SynthSenderRaw(HardwareSerial* serial) : transmitter{serial} {}
  virtual ~SynthSenderRaw() = default;

  // prepare input started message for synth
  void StartInput(uint8_t channel) {
    Send(channel, kChannelActionPlay);
    Debug("Sent <PLay> on channel " + channel);
  }

  // prepare input stop message for synth
  void StopInput(uint8_t channel) {
    Send(channel, kChannelActionStop);
    Debug("Sent <STop> on channel " + channel);
  }
};

}  // namespace audio
}  // namespace kss
