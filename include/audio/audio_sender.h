#pragma once

#include <HardwareSerial.h>  // for HardwareSerial

#include "audio/constants.h"     // for k*
#include "serial/transmitter.h"  // for Transmitter

namespace kss {
namespace audio {

class AudioSender {
  serial::Transmitter transmitter;

  // Set up a message with the header info regarding audio channel and action
  inline const void InitMessage(char* buffer, int channel, char start_stop) {
    buffer[0] = GetChannelMarker(channel);
    buffer[1] = start_stop;
    buffer[2] = '\0';
  }

 public:
  // Constructor: starts serial connection to audioSlave
  AudioSender(HardwareSerial* serial = &Serial1) : transmitter{serial} {}

  // prepare message for audioslave to play audio file
  const void PlayWav(const char* fileName, const int channel = -1) {
    char msg[15];
	InitMessage(msg, channel, kChannelActionPlay);
    strcat(msg, fileName);
    transmitter.Send(msg);
  }

  // prepare message for audioslave to repeat an audio file
  const void RepeatWav(const char* fileName, const size_t channel) {
    char msg[15];
	InitMessage(msg, channel, kChannelActionRepeat);
    strcat(msg, fileName);
    transmitter.Send(msg);
  }

  // prepare message for audioslave to stop audio file
  const void StopChannel(const size_t channel) {
    char msg[3];
	InitMessage(msg, channel, kChannelActionStop);
    transmitter.Send(msg);
  }
};

}  // namespace audio
}  // namespace kss
