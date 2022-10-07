#pragma once

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "engines/noise.h"        // for NoiseGenerator
#include "math/random.h"          // for random::*
#include "time/now.h"             // for Now

namespace kss {
namespace animation {

class Flicker : public Animation {
 private:
  int hueMain = 0;
  int hueAccent = 0;
  int height;
  int* currentHeight;  //<-- stores height data
  int maxHeight = origin + height;
  int width;
  int shiftSpeed = 1;

  // frame rate
  uint32_t frameRateMillis = 10;
  uint32_t flareFrameMillis = frameRateMillis / 2;
  uint32_t lastLoopMillis;
  uint32_t lastFlareMillis;
  uint32_t newMillis;

  // flare
  int flareChance = 2;
  bool* hasFlare;
  int** flareLoc;

  // engines::NoiseGenerator noise;

 public:
  int saturation = 255;
  int brightness = 150;
  int origin;

  // Initialize a Flame at y-location origin with a certain height, main color
  // and accent color
  Flicker(int origin, int height, int width, int hueMain, int hueAccent)
      : Animation(),
        hueMain{hueMain},
        hueAccent{hueAccent},
        height{height},
        width{width},
        origin{origin} /*, noise{width, height}*/ {
    currentHeight = new int[width];

    hasFlare = new bool[width];
    flareLoc = new int*[width];

    for (int i = 0; i < width; i++) {
      currentHeight[i] = height / 2;
      hasFlare[i] = false;
      flareLoc[i] = new int[0];
      flareLoc[i][0] = maxHeight - 1;
      Serial.println("FlameAni: Height " + (String)i + ": " +
                     (String)currentHeight[i]);
    }

    // randomly set first height
    int heightMod = math::random::Int16_incl(height);
    int newHeight = origin + heightMod;
    currentHeight[0] = newHeight;
  }

  // Sets the starting hue, probably not needed since the hue shifts constantly
  void setHues(int mainHue, int accentHue) {
    hueMain = mainHue;
    hueAccent = accentHue;
  }

  // Sets the saturation, 0=white 255=full color
  void setSaturation(int sat) { saturation = sat; }

  // Sets the Brightness, 0=off 255=max
  void setBrightness(int bright) { brightness = bright; }

  // Sets the flame shift rate or how much
  void setSpeed(int speed) { shiftSpeed = speed; }

  void heightCheck(int index) {
    if (currentHeight[index] <= origin) {
      currentHeight[index] = origin;
    } else if (currentHeight[index] >= maxHeight) {
      currentHeight[index] = origin + height;
    }
  }

  // Conjure the Flame
  void Draw(display::Display* display) {
    // noise.fillnoise8();
    newMillis = time::Now();

    // Serial.println("old: " + (String)lastLoopMillis);
    // Serial.println("new: " + (String)newMillis);
    // Serial.println("=============================");

    if ((newMillis - lastLoopMillis) >= frameRateMillis) {
      // adjust
      int16_t heightAdjust = math::random::Int16_incl(-2, 2);
      currentHeight[0] += heightAdjust;
      heightCheck(0);

      Serial.println("FlameAni: 0 Height: " + (String)currentHeight[0]);
      for (int i = 1; i < display->size.x; i++) {
        // Set flame height
        if (math::random::Bool()) {
          heightAdjust *= -1;
        }
        currentHeight[i] = currentHeight[i - 1] + heightAdjust;

        heightCheck(i);
        // flare logic
        if (!hasFlare[i] && currentHeight[i] <= (maxHeight - 2)) {
          hasFlare[i] = true;
          flareLoc[i][0] = currentHeight[i];
        }
        heightCheck(i - 1);
      }
      heightCheck(width - 1);
      lastLoopMillis = time::Now();
      // }
      // //flare logic
      // if((newMillis-lastLoopMillis)>=lastFlareMillis)
      // {
      for (int i = 0; i < display->size.x; i++) {
        // move flare up one
        flareLoc[i][0] += 1;
        // if at max, remove flag to Draw next loop
        if (flareLoc[i][0] == maxHeight + 1) {
          hasFlare[i] = false;
        } else if (math::random::Bool()) {
          hasFlare[i] = false;
        }
      }
      // lastFlareMillis = time::Now();
    }

    // Draw flames
    drawFramesUp(display);
  }

  void drawFramesUp(display::Display* display) {
    for (int i = 0; i < display->size.x; i++) {
      for (int j = origin; j <= currentHeight[i]; j++) {
        // Serial.println("Flame Ani: in the loops");
        // secondary color on last pixel
        if (j == (currentHeight[i]) || j == (currentHeight[i] - 1)) {
          // display->Pixel(i, j) = CHSV(hueAccent, saturation, brightness);
          // display->Pixel(i, j).setHSV(hueAccent, saturation, brightness +
          // noise.Data(i, flareLoc[i][0]));
          display->Pixel(i, j).setHSV(hueAccent, saturation, 255);
        }
        // main color on remaining pixel
        else {
          // display->Pixel(i, j).setHSV(hueMain, saturation, brightness +
          // noise.Data(i, flareLoc[i][0]));
          display->Pixel(i, j).setHSV(hueMain, saturation, 255);
          // display->Pixel(i, j) = CHSV(hueMain, saturation, brightness);
        }
      }

      // Draw Flare
      if (hasFlare[i]) {
        CRGB color;
        display->Pixel(i, flareLoc[i][0]).setHSV(hueAccent, saturation, 255);
        // display->Pixel(i, flareLoc[i][0]).setHSV(hueAccent, saturation,
        // brightness + noise.Data(i, flareLoc[i][0]));
      }
    }
  }
  void drawFramesDown(display::Display* display) {
    for (int i = 0; i < display->size.x; i++) {
      for (int j = origin; j <= currentHeight[i]; j++) {
        // Serial.println("Flame Ani: in the loops");
        // secondary color on last pixel
        if (j == (currentHeight[i]) || j == (currentHeight[i] - 1)) {
          // display->Pixel(i, j) = CHSV(hueAccent, saturation, brightness);
          // display->Pixel(i, j).setHSV(hueAccent, saturation, brightness +
          // noise.Data(i, flareLoc[i][0]));
          display->Pixel(i, j).setHSV(hueAccent, saturation, 255);
        }
        // main color on remaining pixel
        else {
          // display->Pixel(i, j).setHSV(hueMain, saturation, brightness +
          // noise.Data(i, flareLoc[i][0]));
          display->Pixel(i, j).setHSV(hueMain, saturation, 255);
          // display->Pixel(i, j) = CHSV(hueMain, saturation, brightness);
        }
      }

      // Draw Flare
      if (hasFlare[i]) {
        CRGB color;
        display->Pixel(i, flareLoc[i][0]).setHSV(hueAccent, saturation, 255);
        // display->Pixel(i][flareLoc[i, 0]).setHSV(hueAccent, saturation,
        // brightness + noise.Data(i, flareLoc[i][0]));
      }
    }
  }
};

}  // namespace animation
}  // namespace kss
