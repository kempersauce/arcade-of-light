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
#include "time/now.h"         // for Now

namespace kss {
namespace audio {

namespace _channel {

constexpr uint32_t kStartLeadTimeMillis{25};
constexpr float kMaxGain{1.0f};

}  // namespace _channel
using namespace _channel;

// TODO modify this to create patch cables after construction
// so output can be created down-stream from the wav player
// Otherwise we incur a memory penalty and roughly
// a 3ms lag time

class Channel {
  const size_t channel_no;
  AudioPlaySdWav* wav_player;

  AudioMixer4* mixer_left;
  AudioMixer4* mixer_right;

  String current_file;
  bool repeat{false};
  uint32_t start_time;

  float gain_coefficient{1.0f};

  void PlayCurrentFile() {
    if (wav_player->isPlaying()) {
      Debug("Channel[" + channel_no +
            "] is already playing, but is requested to play \"" + current_file +
            "\"");
    }

    if (!wav_player->play(current_file.c_str())) {
      Debug("Channel[" + channel_no + "]: Error playing file: \"" +
            current_file + "\"");
    } else {
      start_time = time::Now();
      Debug("Channel[" + channel_no + "] Playing file: \"" + current_file +
            "\"");
    }
  }

 public:
  Channel(AudioPlaySdWav* wav_player, AudioMixer4* mixer_left,
          AudioMixer4* mixer_right, size_t channel_no)
      : channel_no{channel_no},
        wav_player{wav_player},
        mixer_left{mixer_left},
        mixer_right{mixer_right} {}

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

  void SetGainCoefficient(float gain_coef) { gain_coefficient = gain_coef; }

  void SetGain(float gain) {
    const uint8_t mixer_index = channel_no % 4;
    gain *= gain_coefficient;
    if (gain > kMaxGain) {
      gain = kMaxGain;
    }
    mixer_left->gain(mixer_index, gain);
    mixer_right->gain(mixer_index, gain);
  }

  bool IsPlaying() const {
    // TODO - handle edge case where repeat=true
    // but wav_player has stopped before Update() was called

    // Show as active if we've just started, isPlaying() may not be true yet
    if (start_time != 0 && time::Now() - start_time <= kStartLeadTimeMillis) {
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
