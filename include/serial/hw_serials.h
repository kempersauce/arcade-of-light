#pragma once

#include <HardwareSerial.h>  // for Serial*

namespace kss {
namespace serial {

constexpr HardwareSerial* kHwSerials[4]{
    // clang-format off
	&Serial1,
	&Serial2,
	&Serial3,
	&Serial4
    // clang-format on
};

}  // namespace serial
}  // namespace kss
