#pragma once

#include <Audio.h>

#include <vector>

#include "audio/channel.h"    // for Channel
#include "audio/constants.h"  // for k*
#include "serial/debug.h"     // for Debug

namespace kss {
namespace audio {

class WavAudioManager {
  static constexpr unsigned char L{0};
  static constexpr unsigned char R{1};
  std::vector<Channel> channels;

  static constexpr size_t block_count{kChannelCount};
  static constexpr size_t mixer_count{4};

  AudioPlaySdWav wav_players[kChannelCount];
  AudioMixer4 mixers_left[mixer_count / 2];
  AudioMixer4 mixers_right[mixer_count / 2];
  AudioMixer4 mixer_out_left, mixer_out_right;

  AudioOutputI2S audioOutput;

  AudioConnection patch_cords[18]{
      // clang-format off
	  
      // Patch wav players left channel to mixers
      {wav_players[0], L, mixers_left[0], 0},
      {wav_players[1], L, mixers_left[0], 1},
      {wav_players[2], L, mixers_left[0], 2},
      {wav_players[3], L, mixers_left[0], 3},

      {wav_players[4], L, mixers_left[1], 0},
      {wav_players[5], L, mixers_left[1], 1},
    //   {wav_players[6], L, mixers_left[1], 2},
    //   {wav_players[7], L, mixers_left[1], 3},

      // Patch left mixers to 2nd level output mixer
      {mixers_left[0], 0, mixer_out_left, 0},
      {mixers_left[1], 0, mixer_out_left, 1},

	  // Patch 2nd level output mixer to left output
      {mixer_out_left, 0, audioOutput, L},

      // Patch wav players right channel to mixers
      {wav_players[0], R, mixers_right[0], 0},
      {wav_players[1], R, mixers_right[0], 1},
      {wav_players[2], R, mixers_right[0], 2},
      {wav_players[3], R, mixers_right[0], 3},

      {wav_players[4], R, mixers_right[1], 0},
      {wav_players[5], R, mixers_right[1], 1},
    //   {wav_players[6], R, mixers_right[1], 2},
    //   {wav_players[7], R, mixers_right[1], 3},

      // Patch right mixers to 2nd level output mixer
      {mixers_right[0], 0, mixer_out_right, 0},
      {mixers_right[1], 0, mixer_out_right, 1},

	  // Patch 2nd level output mixer to right output
      {mixer_out_right, 0, audioOutput, R}

      // clang-format on
  };

 public:
  WavAudioManager() {
    for (size_t i = 0; i < block_count; ++i) {
      const size_t mixer_index = i / 4;
      channels.emplace_back(&wav_players[i], &mixers_left[mixer_index],
                            &mixers_right[mixer_index], i);
    }
  }

  Channel& GetChannelByIndex(const size_t index) { return channels[index]; }

  Channel& GetIdleChannel() {
    const static size_t first_channel = 4;

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
