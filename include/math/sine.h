#pragma once

#include <FastLed.h>  // for sin8
#include <math.h>     // for fmod

#include "time/now.h"  // for Now

namespace kss {
namespace math {

class SineWaveGenerator {
  float distance_offset{0};

 public:
  // sine wavelength in pixels
  float wavelength;
  float amplitude;

  // pixels per millisecond
  float speed;

  SineWaveGenerator(float wavelength, float amplitude, float speed)
      : wavelength{wavelength}, amplitude{amplitude}, speed{speed} {}

  void Move() {
    distance_offset =
        fmod(distance_offset + time::LoopElapsedMillis() * speed, wavelength);
  }

  virtual float GetVal(const float distance) const {
    float theta = fmod(1 + (distance + distance_offset) / wavelength, 1);
    const float sine = ((float)sin8(255.0f * theta) - 128.0f) / 128.0f;
    // const float sine = sin(TWO_PI * theta);
    return amplitude * sine;
  }
};

class SineWaveGeneratorRamped {
  SineWaveGenerator wave;
  bool is_active{false};

  static constexpr uint32_t ramp_time_millis{100};
  static constexpr uint32_t decay_time_millis{175};
  uint32_t switch_time{0};

 public:
  SineWaveGeneratorRamped(float wavelength, float amplitude, float speed)
      : wave{wavelength, amplitude, speed} {}

  void On() {
    is_active = true;
    switch_time = time::Now();
  }

  void Off() {
    is_active = false;
    switch_time = time::Now();
  }

  void Move() { wave.Move(); }

  float GetVal(const float distance) const {
    const uint32_t time_since_switch = time::Now() - switch_time;
    float ramp;

    // Ramping into the animation
    if (is_active && time_since_switch < ramp_time_millis) {
      ramp = (float)time_since_switch / (float)ramp_time_millis;
    }

    // Decaying off the animation
    else if (!is_active && time_since_switch < decay_time_millis) {
      ramp = 1.0f - ((float)time_since_switch / decay_time_millis);
    }

    // Past the end of the animation
    else if (!is_active) {
      return 0;
    }

    // Full strength for mid animation
    else {
      ramp = 1;
    }

    return ramp * wave.GetVal(distance);
  }
};

}  // namespace math
}  // namespace kss
