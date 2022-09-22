#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "math/random.h"          // for random::*
#include "time/now.h"             // for Now

namespace kss {
namespace games {
namespace rocket {

/*Target Class
Class that sets a series of dots in a specific location on the LED strip
*/
class Target : public animation::Animation {
  const static uint32_t targetLockTimeMillis = 1000 * 3;  // 3 second lock time
 public:
  size_t Loc;
  size_t Height;
  CRGB* color;
  uint32_t Time;
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

  bool isTargetLocked() const {
    return isInTarget && time::Now() - Time > targetLockTimeMillis;
  }

  void draw(display::Display* display) {
    const size_t bottom = Loc;
    const size_t top = bottom + Height;

    // Draw the target accross all strips
    for (size_t x = 0; x < display->size.x; ++x) {
      // Target bookends
      if (bottom >= 0) {
        display->Pixel(x, bottom) = *color;
      }

      if (top >= 0) {
        display->Pixel(x, top) = *color;
      }

      if (isInTarget) {
        long timeHeld = time::Now() - Time;
        float offset = (float)(Height / 2) *
                       ((float)timeHeld /
                        (float)targetLockTimeMillis);  // up to half height over
                                                       // target lock time

        // Bottom fill
        size_t bottomFillStart = bottom;
        float bottomFillEnd = (float)bottomFillStart + offset;
        for (size_t i = bottomFillStart; i < bottomFillEnd; i++) {
          display->Pixel(x, i) = *color;
        }
        display->DitherPixel(x, bottomFillEnd, color);

        // Top fill
        size_t topFillEnd = top;
        float topFillStart = (float)topFillEnd - offset;
        for (size_t i = ceil(topFillStart); i < topFillEnd; i++) {
          display->Pixel(x, i) = *color;
        }
        display->DitherPixel(x, topFillStart, color);
      }
    }
  }
};

}  // namespace rocket
}  // namespace games
}  // namespace kss
