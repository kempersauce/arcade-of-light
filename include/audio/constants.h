#pragma once

#include "serial/debug.h"  // for Debug

namespace kss {
namespace audio {

constexpr size_t kChannelCount{5};

// Message actions
constexpr char kActionChannelPlay{'1'};
constexpr char kActionChannelStop{'0'};
constexpr char kActionChannelRepeat{'2'};
constexpr char kActionClickTrack{'c'};

// Message channels
constexpr char kChannelMarkerBG{'0'};
constexpr char kChannelMarker1{'1'};
constexpr char kChannelMarker2{'2'};
constexpr char kChannelMarkerAny{'?'};

// SYNTH RECIEVER CONTROL MAPPINGS
constexpr uint8_t kRightChannelNum = 3;
constexpr uint8_t kLeftChannelNum = 2;
constexpr uint8_t kUpChannelNum = 0;
constexpr uint8_t kDownChannelNum = 1;
constexpr uint8_t kAChannelNum = 4;
constexpr uint8_t kBChannelNum = 5;

struct SynthAudioMessage {
  uint8_t action;
  uint8_t channel;
};

struct WavAudioMessage {
  char channel_selector;
  char action_selector;
  char filename[13];  // 8 chars for name, 1 for ., 3 for WAV, 1 for \0
};

// Translate an integer index into a channel marker
const inline char GetChannelMarker(const int channel_index) {
  switch (channel_index) {
    case 0:
      return kChannelMarkerBG;

    case 1:
      return kChannelMarker1;

    case 2:
      return kChannelMarker2;

      // Default to an unspecified channel
    case -1:
    default:
      return kChannelMarkerAny;
  }
}

// Translate a channel marker char to integer index
const inline size_t GetChannelIndex(const char channel_marker) {
  switch (channel_marker) {
    case kChannelMarkerBG:
      return 0;

    case kChannelMarker1:
      return 1;

    case kChannelMarker2:
      return 2;

    default:  // target channel one by default I guess
      Debug("ERROR: Received invalid channel marker character: '" +
            channel_marker + "'");
      return kChannelMarker1;
  }
}

}  // namespace audio
}  // namespace kss
