#pragma once

#include <Arduino.h>  // for millis()

namespace kss {
namespace time {

namespace _now {
uint32_t last_loop_time{0};
uint32_t loop_time{0};
}  // namespace _now

inline const void SetLoopTime() {
  _now::last_loop_time = _now::loop_time;
  _now::loop_time = millis();
}

inline const uint32_t Now() {
  if (_now::loop_time == 0) {
    return millis();
  }
  return _now::loop_time;
}

inline const uint32_t ElapsedMillis() {
  return _now::loop_time - _now::last_loop_time;
}

}  // namespace time
}  // namespace kss
