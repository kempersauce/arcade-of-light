#pragma once

namespace kss {
namespace audio {

constexpr size_t kChannelCount{5};

constexpr char kChannelActionPlay{'1'};
constexpr char kChannelActionStop{'0'};
constexpr char kChannelActionRepeat{'2'};

constexpr char kChannelMarkerBG{'0'};
constexpr char kChannelMarker1{'1'};
constexpr char kChannelMarker2{'2'};
constexpr char kChannelMarkerAny{'?'};

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
      return kChannelMarker1;
  }
}

}  // namespace audio
}  // namespace kss
