#pragma once

// TODO figure out a better way to split these constants
#include "../shared/serial/constants.h"

namespace kss {
namespace serial {

constexpr size_t kMessageBufferSize{32};
constexpr char kMessageStartMarker{'<'};
constexpr char kMessageEndMarker{'>'};

}  // namespace serial
}  // namespace kss
