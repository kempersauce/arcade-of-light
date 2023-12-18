#pragma once

#include "serial/debug.h"  // for Debug

namespace kss {
namespace audio {

constexpr size_t kChannelCount{6};

// Message actions
constexpr char kActionChannelPlay{'P'};
constexpr char kActionChannelStop{'S'};
constexpr char kActionChannelRepeat{'R'};
constexpr char kActionChannelGain{'G'};
constexpr char kActionClickTrack{'c'};

// Message channels
constexpr char kChannelMarker0{'0'};
constexpr char kChannelMarker1{'1'};
constexpr char kChannelMarker2{'2'};
constexpr char kChannelMarker3{'3'};
constexpr char kChannelMarker4{'4'};
constexpr char kChannelMarker5{'5'};
constexpr char kChannelMarker6{'6'};
constexpr char kChannelMarker7{'7'};

constexpr char kChannelMarkerBG{kChannelMarker0};
constexpr char kChannelMarkerAny{'?'};

// SYNTH RECIEVER CONTROL MAPPINGS
constexpr uint8_t kBChannelNum = 0;
constexpr uint8_t kAChannelNum = 1;
constexpr uint8_t kDownChannelNum = 2;
constexpr uint8_t kLeftChannelNum = 3;
constexpr uint8_t kRightChannelNum = 4;
constexpr uint8_t kUpChannelNum = 5;

struct SynthAudioMessage {
  uint8_t action;
  uint8_t channel;
};

struct WavAudioMessage {
  char channel_selector;
  char action_selector;
  char filename[13];  // 8 chars for name, 1 for ., 3 for WAV, 1 for \0
  float gain;
};

// Translate an integer index into a channel marker
const inline char GetChannelMarker(const int channel_index) {
  switch (channel_index) {
    case 0:
      return kChannelMarker0;

    case 1:
      return kChannelMarker1;

    case 2:
      return kChannelMarker2;

    case 3:
      return kChannelMarker3;

    case 4:
      return kChannelMarker4;

    case 5:
      return kChannelMarker5; 

    case 6:
      return kChannelMarker6; 

    case 7:
      return kChannelMarker7;       

      // Default to an unspecified channel
    case -1:
    default:
      return kChannelMarkerAny;
  }
}

// Translate a channel marker char to integer index
const inline size_t GetChannelIndex(const char channel_marker) {
  switch (channel_marker) {
    case kChannelMarker0:
      return 0;

    case kChannelMarker1:
      return 1;

    case kChannelMarker2:
      return 2;

    case kChannelMarker3:
      return 3;

    case kChannelMarker4:
      return 4;

    case kChannelMarker5:
      return 5;

    case kChannelMarker6:
      return 6;

    case kChannelMarker7:
      return 7;

    default:  // target channel one by default I guess (not BG channel)
      Debug("ERROR: Received invalid channel marker character: '" +
            channel_marker + "'");
      return kChannelMarker1;
  }
}

}  // namespace audio
}  // namespace kss
