#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "math/random.h"          // for random::*

namespace kss {
namespace games {
namespace rocket {

/*Target Class
Class that sets a series of dots in a specific location on the LED strip
*/
class Target : public animation::Animation {
  const static long targetLockTimeMillis = 1000 * 3;  // 3 second lock time
 public:
  int Loc;
  int Height;
  CRGB* color;
  long Time;
  bool isInTarget;

  // Constructor
  Target(CRGB* clr) : Animation() {
    color = clr;
    Time = 0;
    isInTarget = false;
  }

  void setColor(CRGB* clr) { color = clr; }

  void randomize(int strip_length) {
    Loc = math::random::Int16(strip_length / 4, strip_length - 20);
    Height = math::random::Int8(10, 25);
  }

  void setToGround() {
    Loc = 0;
    Height = 10;
  }

  bool isTargetLocked() {
    return isInTarget && millis() - Time > targetLockTimeMillis;
  }

  void draw(display::Display* display) {
    int bottom = Loc;
    int top = bottom + Height;

    // Draw the target accross all strip_count
    for (int j = 0; j < display->strip_count; j++) {
      // Target bookends
      if (bottom >= 0) display->Pixel(j, bottom) = *color;

      if (top >= 0) display->Pixel(j, top) = *color;

      if (isInTarget) {
        long timeHeld = millis() - Time;
        float offset = (float)(Height / 2) *
                       ((float)timeHeld /
                        (float)targetLockTimeMillis);  // up to half height over
                                                       // target lock time

        // Bottom fill
        int bottomFillStart = bottom;
        float bottomFillEnd = (float)bottomFillStart + offset;
        for (int i = bottomFillStart; i < bottomFillEnd; i++) {
          display->Pixel(j, i) = *color;
        }
        display->DitherPixel(j, bottomFillEnd, color);

        // Top fill
        int topFillEnd = top;
        float topFillStart = (float)topFillEnd - offset;
        for (int i = ceil(topFillStart); i < topFillEnd; i++) {
          display->Pixel(j, i) = *color;
        }
        display->DitherPixel(j, topFillStart, color);
      }
    }
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
