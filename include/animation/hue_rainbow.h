#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display

namespace kss {
namespace animation {

class HueRainbow : public Animation {
 private:
  int HueStart = 0;
  int Beats = 3;
  int Min = -15;
  int Max = 15;

 public:
  int Saturation = 255;
  int Brightness = 150;
  int ShiftSpeed = 5;
  bool WaveShift = false;

  // Initialize a HueRainbow that will shift at set rate, realistically this
  // should be between -20 and 20
  HueRainbow(int speed) : Animation() { ShiftSpeed = speed; }
  // Sets the starting hue, probably not needed since the hue shifts constantly
  void setHue(int hue) { HueStart = hue; }
  // Sets the saturation, 0=white 255=full color
  void setSaturation(int sat) { Saturation = sat; }
  // Sets the Brightness, 0=off 255=max
  void setBrightness(int bright) { Brightness = bright; }

  // Sets the rainbow shift rate, realistically this should be between -20 and
  // 20 A negative number will make the rainbow flow up the strip a positive
  // number will make the number flow down the strip
  void setSpeed(int speed) { ShiftSpeed = speed; }
  // Enables variable shift rates based on a sin function
  void setWaveShift(bool wave) { WaveShift = wave; }
  // Customizes the sin function, Beats is how many waves per second, min is the
  // min shift speed, max is the max shift speed
  void setWaveStats(int beats, int min, int max) {
    Beats = beats;
    Min = min;
    Max = max;
  }
  // Taste the rainbow
  void draw(Display* display) {
    for (int i = 0; i < display->numStrips; i++) {
      int Hue = HueStart + (i * ShiftSpeed);
      for (int j = 0; j < display->lengthStrips; j++) {
        Hue = (Hue + 256) % 256;  // black magic muwhahaha
        display->strips[i][j] = CHSV(Hue, Saturation, Brightness);

        if (ShiftSpeed >= 0) {
          Hue++;
        } else {
          Hue--;
        }
      }
    }

    if (WaveShift) {
      ShiftSpeed = beatsin8(Beats, Min, Max);
    }

    HueStart = (HueStart + ShiftSpeed) % 256;
  }
};

}  // namespace animation
}  // namespace kss
