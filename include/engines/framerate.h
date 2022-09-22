#pragma once

#include <FastLED.h>  // for FastLED

#include "time/now.h"  // for Now

namespace kss {
namespace engines {

class FrameRate {
  uint32_t last_frame_millis_{time::Now()};

 public:
  void PrintFrameRate() {
    const auto now = time::Now();
    const auto timeDiff = now - last_frame_millis_;
    const auto fps = 1000 / timeDiff;
    last_frame_millis_ = now;

    const auto fast_led_fps = FastLED.getFPS();
    Serial.println((String) "FPS: " + fps + " | " + timeDiff +
                   "ms | reported: " + fast_led_fps);
  }
};

}  // namespace engines
}  // namespace kss
