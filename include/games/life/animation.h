#pragma once

#include <FastLED.h>

#include <vector>

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "math/random.h"          // for random::*

namespace kss {
namespace games {
namespace life {

class LifeAnimation : public animation::Animation {
 private:
  size_t width;
  size_t height;

  // We need 2 frames to write the changes each round
  int** frame1;  //[NUM_STRIPS][NUM_LEDS];
  int** frame2;

  // Keep pointers to the frames so we can easily swap them each round instead
  // of copying
  int*** lastRound = &frame1;
  int*** nextRound = &frame2;

 public:
  float randomizeDensity = .2;

  std::vector<CRGB> ageColors{
      CRGB(0, 0, 0),      // black
      CRGB(0, 255, 0),    // green
      CRGB(0, 255, 255),  // cyan
      CRGB(0, 0, 255),    // blue
      CRGB(255, 0, 255),  // magenta
      CRGB(255, 0, 0),    // red
      CRGB(255, 255, 0),  // yellow
  };

  LifeAnimation(size_t width, size_t height)
      : Animation(), width{width}, height{height} {
    frame1 = new int*[width];
    frame2 = new int*[width];
    for (int i = 0; i < width; i++) {
      frame1[i] = new int[height];
      frame2[i] = new int[height];
    }

    lastRound = &frame1;
    nextRound = &frame2;

    randomize();  // init the nextRound just to be safe
  }

  void setCellState(size_t x, size_t y, bool state) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
      (*nextRound)[x][y] = state ? 1 : 0;
    }
  }

  void GoOneRound() {
    // swap last round with next round
    int*** placeholder = lastRound;
    lastRound = nextRound;
    nextRound = placeholder;

    // Calculate the next round based on the last one
    for (size_t strip = 0; strip < width; strip++) {
      for (size_t led = 0; led < height; led++) {
        int neighborsAlive = 0;
        for (int i = -1; i <= 1; i++) {
          for (int j = -1; j <= 1; j++) {
            // don't count *this* cell
            if (i == 0 && j == 0) {
              continue;
            }

            // calculate neighbor cell indices
            size_t neighborStrip = (strip + i + width) % width;
            size_t neighborLED = (led + j + height) % height;

            // count up the 'alive' neighbors in the last round
            if ((*lastRound)[neighborStrip][neighborLED] > 0) {
              neighborsAlive++;
            }
          }
        }

        int age = (*lastRound)[strip][led];  // 0 means dead
        if (neighborsAlive < 2) {
          age = 0;  // dead
        } else if (neighborsAlive > 3) {
          age = 0;  // dead;
        } else if (neighborsAlive == 3) {
          age++;  // bring the dead to life! and increment living cells
        } else {
          // the old get older but nobody gets born here
          if (age > 0) {
            age++;
          }
        }

        (*nextRound)[strip][led] = age;
      }
    }
  }

  void Draw(display::Display* display) {
    for (size_t ledIndex = 0; ledIndex < display->size.y; ledIndex++) {
      for (size_t stripIndex = 0; stripIndex < display->size.x; stripIndex++) {
        int age = (*nextRound)[stripIndex][ledIndex];

        // Dont let it step past the array bounds
        if (age >= ageColors.size()) {
          age = ageColors.size() - 1;
        }

        display->Pixel(stripIndex, ledIndex) = ageColors[age];
      }
    }
  }

  void randomize() {
    for (size_t i = 0; i < width; i++) {
      for (size_t j = 0; j < height; j++) {
        const bool alive = math::random::Bool(randomizeDensity);
        if (alive) {
          (*nextRound)[i][j] = 1;
        } else {
          (*nextRound)[i][j] = 0;
        }
      }
    }
  }
};

}  // namespace life
}  // namespace games
}  // namespace kss
