#pragma once

#include <Arduino.h>
#include <HardwareSerial.h>  // for HardwareSerial

namespace kss {
namespace audio {

class AudioSender {
  HardwareSerial& serial = Serial1;
  const char* startSymbol = "<";
  const char* endSymbol = ">";
  const char* startChannelChar = "1";
  const char* stopChannelChar = "0";

  const char* zero = "0";
  const char* one = "1";
  const char* two = "2";

  uint32_t delayStartMillis;
  bool delayHasStarted = false;
  bool delaySoundPlayed = false;

  // helper function because I'm bad at C++ and char array concatination
  // TODO - should we implement a map of int->char?
  // then we could use custom channel markers like 'B' for background etc
  const inline char* GetChannelChar(const int channel) {
    switch (channel) {
      case 0:
        return zero;
      case 1:
        return one;
      case 2:
        return two;

      default:
        return one;
    }
  }

  // send message over serial to audioslave
  const void SendMsg(const char* msg) {
	// Print this to both serial AND Serial
    serial.println(msg);
    Serial.println(msg);
  }

 public:
  // Constructor: starts serial connection to audioSlave
  AudioSender() { serial.begin(115200); }

  // prepare message for audioslave to play audio file
  const void PlayWav(const char* fileName, const int channel = -1) {
    char msg[12];
    strcpy(msg, startSymbol);
    if (channel >= 0) {
      strcpy(msg, GetChannelChar(channel));
      strcat(msg, startChannelChar);
    }
    strcat(msg, fileName);
    strcat(msg, endSymbol);
    SendMsg(msg);
  }

  const void StopChannel(const int channelNum) {
    char msg[12];
    strcpy(msg, startSymbol);
    strcat(msg, GetChannelChar(channelNum));
    strcat(msg, stopChannelChar);
    strcat(msg, endSymbol);
    SendMsg(msg);
  }

  const void setBackground(const char* fileName) { PlayWav(fileName, 0); }
};

}  // namespace audio
}  // namespace kss
