#pragma once

#include <Animation.h>
#include <Display.h>

// Single color background
class SingleColorBlock : Animation {
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

  void draw(Display* display) {
    for (int i = 0; i < display->numStrips; i++) {
      for (int j = HeightMin; j < HeightMax; j++) {
        display->strips[i][j].setHSV(Hue, Saturation, Value);
      }
    }
  }
};
