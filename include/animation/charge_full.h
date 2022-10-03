#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

// Single color background
class ChargeFull : public Animation {
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
  size_t zone_size = 20;
  float border_blend = .5;

  bool WaveShift = true;

  // Initialize a HueRainbow that will shift at set rate, realistically this
  // should be between -20 and 20
  ChargeFull(int8_t speed, size_t wave_length = 100)
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

  void Move() {
    // TODO move this to be based on time, not framerate
    HueStart += ShiftSpeed;
  }

  // Taste the rainbow
  void Draw(display::Display* display) {
    uint8_t y_limit = display->size.y - 1;
    uint8_t x_limit = display->size.x - 1;
    CRGB color;

    for (size_t x = 0; x < display->size.x; ++x) {
      float hue = HueStart + (x * ShiftSpeed);
      for (size_t y = 0; y < display->size.y / 2; ++y) {
        // Normalize hue to 0-255
		hue = fmod(hue, 256);
        color.setHSV(hue, Saturation, 255);
        if (x == 0 || x == x_limit || y == 0) {
          display->BlendPixel(x, y, &color, border_blend);
          display->BlendPixel(x, y_limit - y, &color, border_blend);
        } else if (y < zone_size) {
          float blendFactor = border_blend * (zone_size - y) / zone_size;
          display->BlendPixel(x, y, &color, blendFactor);
          display->BlendPixel(x, y_limit - y, &color, blendFactor);
        }
        hue += hue_diff_per_pixel;
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
