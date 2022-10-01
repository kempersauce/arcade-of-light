#pragma once

#include <Arduino.h>  // for uint8_t ... wow

namespace kss {
namespace audio {
namespace beats {

constexpr uint8_t kChannelTom{0};
constexpr uint8_t kChannelHHClosed{1};
constexpr uint8_t kChannelCrash{2};
constexpr uint8_t kChannelClap{3};
constexpr uint8_t kChannelBassDrum{4};
constexpr uint8_t kChannelSnare{5};

}  // namespace beats
}  // namespace audio
}  // namespace kss
