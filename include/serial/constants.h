#pragma once

namespace kss {
namespace serial {

constexpr uint32_t kBaudRate{115200};
constexpr size_t kMessageBufferSize{32};
constexpr char kMessageStartMarker{'<'};
constexpr char kMessageEndMarker{'>'};

}  // namespace serial
}  // namespace kss
