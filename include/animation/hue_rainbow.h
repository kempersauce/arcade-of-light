#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "serial/debug.h"         // for Debug

namespace kss {
namespace animation {

class HueRainbow : public Animation {
 private:
  uint8_t HueStart = 0;
  accum88 bpm = 3 << 8;
  int8_t speed_min = -5;
  int8_t speed_max = 5;

 public:
  uint8_t Saturation = 255;
  uint8_t Brightness = 150;
  int8_t ShiftSpeed = 1;
  float hue_diff_per_pixel = 1;

  bool WaveShift = true;

  // Initialize a HueRainbow that will shift at set rate, realistically this
  // should be between -20 and 20
  HueRainbow(int8_t speed, size_t wave_length = 100)
      : Animation(), ShiftSpeed{speed}, hue_diff_per_pixel{256 / wave_length} {}

  // Sets the starting hue, probably not needed since the hue shifts constantly
  void setHue(uint8_t hue) { HueStart = hue; }

  // Sets the saturation, 0=white 255=full color
  void setSaturation(uint8_t sat) { Saturation = sat; }

  // Sets the Brightness, 0=off 255=max
  void setBrightness(uint8_t bright) { Brightness = bright; }

  // Sets the rainbow shift rate, realistically this should be between -20 and
  // 20 A negative number will make the rainbow flow up the strip a positive
  // number will make the number flow down the strip
  void setSpeed(int speed) { ShiftSpeed = speed; }

  // Enables variable shift rates based on a sin function
  void setWaveShift(bool wave) { WaveShift = wave; }

  // Customizes the sin function, bpm is how many wave oscilations per minute,
  // min is the min shift speed, max is the max shift speed
  void setWaveStats(uint8_t bpm, int8_t min, int8_t max) {
    this->bpm = bpm << 8;
    speed_min = min;
    speed_max = max;
  }

  // Taste the rainbow
  void Draw(display::Display* display) {
    for (size_t x = 0; x < display->size.x; ++x) {
      float hue = HueStart + ((int)x * ShiftSpeed);
      for (size_t y = 0; y < display->size.y; ++y) {
        // Normalize hue to 0-255
        if (hue < 0) {
          hue += 256;
        }
        if (hue >= 256) {
          hue -= 256;
        }
        display->Pixel(x, y) = CHSV((uint8_t)hue, Saturation, Brightness);

        hue += hue_diff_per_pixel;
      }
    }

    if (WaveShift) {
      ShiftSpeed = beatsin8(bpm, 0, speed_max - speed_min) + speed_min;
    }

    HueStart += ShiftSpeed;
  }
};

}  // namespace animation
}  // namespace kss
