#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

// Single color background
class SingleColorBlock : public Animation {
 public:
  // colors (RGB)
  int Hue;
  int Saturation;
  int Value;
  int HeightMin;
  int HeightMax;

  SingleColorBlock(int heightMin, int heightMax, int hue, int saturation,
                   int value)
      : Animation() {
    HeightMin = heightMin;
    HeightMax = heightMax;
    Hue = hue;
    Saturation = saturation;
    Value = value;
  }

  void setColor(int hue, int saturation, int value) {
    Hue = hue;
    Saturation = saturation;
    Value = value;
  }

  void draw(display::Display* display) {
    for (int i = 0; i < display->strip_count; i++) {
      for (int j = HeightMin; j < HeightMax; j++) {
        display->Pixel(i, j).setHSV(Hue, Saturation, Value);
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
