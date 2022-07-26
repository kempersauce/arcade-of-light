#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"  // for display::Display

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

  void randomize(int lengthStrips) {
    Loc = random(lengthStrips / 4, lengthStrips - 20);
    Height = random(10, 25);
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

    // Draw the target accross all numStrips
    for (int j = 0; j < display->numStrips; j++) {
      // Target bookends
      if (bottom >= 0) display->strips[j][bottom] = *color;

      if (top >= 0) display->strips[j][top] = *color;

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
          display->strips[j][i] = *color;
        }
        display->ditherPixel(j, bottomFillEnd, color);

        // Top fill
        int topFillEnd = top;
        float topFillStart = (float)topFillEnd - offset;
        for (int i = ceil(topFillStart); i < topFillEnd; i++) {
          display->strips[j][i] = *color;
        }
        display->ditherPixel(j, topFillStart, color);
      }
    }
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
