#pragma once

#include <Arduino.h>  // for millis()

namespace kss {
namespace time {

namespace _now {
uint32_t loop_time{0};
}  // namespace _now
using namespace _now;

void SetLoopTime() { loop_time = millis(); }

const uint32_t Now() {
  if (loop_time == 0) {
    return millis();
  }
  return loop_time;
}

}  // namespace time
}  // namespace kss
