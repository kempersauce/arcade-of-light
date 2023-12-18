#pragma once

#include <Arduino.h>  // for uint8_t ... wow
#include "audio/constants.h"

namespace kss {
namespace audio {
namespace beats {

constexpr uint8_t kChannelTom{kUpChannelNum};
constexpr uint8_t kChannelHHClosed{kDownChannelNum};
constexpr uint8_t kChannelCrash{kLeftChannelNum};
constexpr uint8_t kChannelClap{kRightChannelNum};
constexpr uint8_t kChannelBassDrum{kAChannelNum};
constexpr uint8_t kChannelSnare{kBChannelNum};

}  // namespace beats
}  // namespace audio
}  // namespace kss
