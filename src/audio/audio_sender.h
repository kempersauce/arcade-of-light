#pragma once

#include <HardwareSerial.h>  // for HardwareSerial

#include "audio/constants.h"        // for k*
#include "serial/ez_transmitter.h"  // for EZTransmitter
#include "serial/hw_serials.h"      // for kHwSerials

namespace kss {
namespace audio {

class AudioSender {
  serial::EZTransmitter<WavAudioMessage> transmitter;

  inline void Send(const char* fileName, const int channel, const char action,
                   float gain = 0) {
    WavAudioMessage msg;
    msg.action_selector = action;
    msg.channel_selector = GetChannelMarker(channel);
    strcpy(msg.filename, fileName);
    msg.gain = gain;
    transmitter.Send(msg);
  }

 public:
  // Constructor: starts serial connection to audioSlave
  AudioSender(HardwareSerial* serial = &Serial1) : transmitter{serial} {}

  void PlayWav(const char* fileName, const int channel = -1) {
    Send(fileName, channel, kActionChannelPlay);
  }

  void RepeatWav(const char* fileName, const size_t channel) {
    Send(fileName, channel, kActionChannelRepeat);
  }

  void StopChannel(const size_t channel) {
    Send("", channel, kActionChannelStop);
  }

  void SetChannelGain(const size_t channel, float gain) {
    Send("", channel, kActionChannelGain, gain);
  }
};

}  // namespace audio
}  // namespace kss
