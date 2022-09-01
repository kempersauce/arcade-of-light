#pragma once

#include <FastLED.h>  // for millis()

namespace kss {
namespace engines {

class FrameRate {
  const uint32_t time_diff_limit;
  uint32_t last_frame_millis_{millis()};

 public:
  FrameRate(uint32_t fps_limit = 9000) : time_diff_limit{1000 / fps_limit} {}

  void PrintFrameRate() {
    const auto now = millis();
    const auto time_diff = now - last_frame_millis_;
    const auto fps = 1000 / time_diff;
    last_frame_millis_ = now;

    const auto fast_led_fps = FastLED.getFPS();
    if (time_diff < time_diff_limit) {
      const auto delay_millis = time_diff_limit - time_diff;
      Serial.println((String) "FPS: " + fps + " | " + time_diff +
                     "ms | reported: " + fast_led_fps +
                     " | delayed for: " + delay_millis);
      delay(delay_millis);
    } else {
      Serial.println((String) "FPS: " + fps + " | " + time_diff +
                     "ms | reported: " + fast_led_fps +
                     " | no delay this time");
    }
  }
};

}  // namespace engines
}  // namespace kss
