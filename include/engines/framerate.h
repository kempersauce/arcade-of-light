#pragma once

#include <FastLED.h>  // for millis()

namespace kss {
namespace engines {

class FrameRate {
  uint32_t last_frame_millis_{millis()};

 public:
  void PrintFrameRate() {
    const auto now = millis();
    const auto timeDiff = now - last_frame_millis_;
    const float fps = (float)timeDiff / 1000.0;
    last_frame_millis_ = now;

    Serial.println((String) "FPS: " + fps + " | " + timeDiff + "ms");
  }
};

}  // namespace engines
}  // namespace kss
