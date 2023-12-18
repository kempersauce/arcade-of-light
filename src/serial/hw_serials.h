#pragma once

#include <HardwareSerial.h>  // for Serial*

namespace kss {
namespace serial {

constexpr size_t kHwSerialCount {
#if defined(ARDUINO_TEENSY41)
  8
#elif defined(ARDUINO_TEENSY40)
  7
#elif defined(ARDUINO_TEENSY36)
  6
#endif
};

constexpr HardwareSerial* kHwSerials[kHwSerialCount] {
  // clang-format off
	&Serial1,
	&Serial2,
	&Serial3,
	&Serial4,
	&Serial5,
	&Serial6
	#if defined(ARDUINO_TEENSY41) || defined(ARDUINO_TEENSY40)
	,&Serial7
	#endif
	#if defined(ARDUINO_TEENSY41)
	,&Serial8
	#endif
  // clang-format on
};

constexpr size_t kCommonSerialCount{4};
constexpr HardwareSerial* kCommonSerials[kCommonSerialCount]{
    // clang-format off
	kHwSerials[0],
	kHwSerials[1],
	kHwSerials[2],
	kHwSerials[3]
    // clang-format on
};

}  // namespace serial
}  // namespace kss
