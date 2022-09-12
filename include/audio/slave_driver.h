#pragma once

#include <Audio.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Wire.h>

#include <string>
#include <vector>

#include <Audio.h>
#include "audio/channel.h"      // for Channel
#include "audio/constants.h"    // for k*
#include "audio/sounds.h"       // for InitAudio
#include "serial/debug.h"       // for Debug

namespace kss {
namespace audio {

class SlaveDriver {
  std::vector<Channel> channels;

  static constexpr size_t block_count{kChannelCount};
  static constexpr size_t mixer_count{2};

  AudioPlaySdWav wav_players[kChannelCount];
  AudioMixer4 mixers[mixer_count];
  AudioMixer4 mixer_out;

  AudioOutputI2S audioOutput;

  std::vector<AudioConnection> patch_cords{
      // Patch background directly to mixer_out
      {wav_players[0], 0, mixer_out, 0},  //
      {wav_players[0], 1, mixer_out, 1},  //

      // Patch wav players to mixers
      {wav_players[1], 0, mixers[0], 0},  //
      {wav_players[1], 1, mixers[0], 1},  //
      {wav_players[2], 0, mixers[0], 2},  //
      {wav_players[2], 1, mixers[0], 3},  //

      {wav_players[3], 0, mixers[1], 0},  //
      {wav_players[3], 1, mixers[1], 1},  //
      {wav_players[4], 0, mixers[1], 2},  //
      {wav_players[4], 1, mixers[1], 3},  //

      // Patch 2nd level mixers to output
      {mixers[0], 0, mixer_out, 2},  //
      {mixers[1], 0, mixer_out, 3},  //

	  // Patch mixer_out to audioOutput
      {mixer_out, 0, audioOutput, 0}, // 
      {mixer_out, 0, audioOutput, 1} //
  };

 public:
  SlaveDriver() {
    for (size_t i = 0; i < block_count; ++i) {
      channels.emplace_back(&wav_players[i], i);
    }
  }

  Channel& GetChannelByIndex(const size_t index) { return channels[index]; }

  Channel& GetIdleChannel() {
    const static size_t first_channel = 3;

    // Find first available channel, starting with first_channel
    for (size_t channel = first_channel; channel < kChannelCount; ++channel) {
      if (!channels[channel].IsPlaying()) {
        return channels[channel];
      }
    }

    // Default to first_channel if they're all already playing something
    Debug("OVERWRITE==OVERWRITE==OVERWRITE (all channels playing)");
    return channels[first_channel];
  }

  Channel& GetChannel(const char channel_marker) {
    if (channel_marker == '?') {
      return GetIdleChannel();
    }

    const size_t index = GetChannelIndex(channel_marker);
    return channels[index];
  }

  // This is left for debug convenience only, unused by production code
  Channel& PlayWav(const char* file_name) {
    Channel& channel = GetIdleChannel();
    channel.Play(file_name);
    return channel;
  }

  void UpdateAll() {
    for (auto& channel : channels) {
      channel.Update();
    }
  }
};

}  // namespace audio
}  // namespace kss
