#pragma once

#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

#include <string>
#include <vector>

#include "audio/constants.h"  // for k*
#include "serial/debug.h"     // for Debug

namespace kss {
namespace audio {

namespace _channel {

constexpr uint32_t kStartLeadTimeMillis{25};

}  // namespace _channel
using namespace _channel;

// TODO modify this to create patch cables after construction
// so output can be created down-stream from the wav player
// Otherwise we incur a memory penalty and roughly
// a 3ms lag time

class Channel {
  const size_t channel_no;
  AudioPlaySdWav* wav_player;

  String current_file;
  bool repeat{false};
  uint32_t start_time;

  void PlayCurrentFile() {
    if (wav_player->isPlaying()) {
      Debug("Channel[" + channel_no +
            "] is already playing, but is requested to play \"" + current_file +
            "\"");
    }

    wav_player->play(current_file.c_str());
    start_time = millis();
    Debug("Channel[" + channel_no + "] Playing file: \"" + current_file + "\"");
  }

 public:
  Channel(AudioPlaySdWav* wav_player, size_t channel_no)
      : channel_no{channel_no}, wav_player{wav_player} {}

  void Play(String file_name) {
    current_file = std::move(file_name);  // cant use file_name after this
    repeat = false;
    PlayCurrentFile();
  }

  void Repeat(String file_name) {
    current_file = std::move(file_name);  // cant use file_name after this
    repeat = true;
    PlayCurrentFile();
  }

  void Stop() {
    start_time = 0;  // TODO we probably don't need this
    repeat = false;
    wav_player->stop();
  }

  bool IsPlaying() const {
    // TODO - handle edge case where repeat=true
    // but wav_player has stopped before Update() was called

    // Show as active if we've just started, isPlaying() may not be true yet
    if (start_time != 0 && millis() - start_time <= kStartLeadTimeMillis) {
      return true;
    }

    return wav_player->isPlaying();
  }

  // Check the internal state of this channel, and perform any necessary actions
  void Update() {
    if (repeat && !IsPlaying()) {
      PlayCurrentFile();
    }
  }
};

}  // namespace audio
}  // namespace kss
