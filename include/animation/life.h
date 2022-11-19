#pragma once

#include <pixeltypes.h>  // for CRGB

#include <algorithm>  // for std::swap
#include <vector>     // for std::vector

#include "animation/animation.h"  // for Animation
#include "display/display.h"      // for Display
#include "math/random.h"          // for random::*
#include "math/vector2d.h"        // for Dimension

namespace kss {
namespace animation {

struct Grid {
  const math::Dimension size;
  std::vector<bool> values;

  Grid(math::Dimension size) : size{size} {
    const auto total = size.width * size.height;
    values.reserve(size.width * size.height);
    while (values.size() < total) {
      values.emplace_back(false);
    }
  }

  inline std::vector<bool>::reference Cell(size_t x, size_t y) {
    return values.at(size.height * x + y);
  }

  void Randomize(float density) {
    for (auto it = values.begin(); it != values.end(); ++it) {
      *it = math::random::Bool(density);
    }
  }
};

class Life : public Animation {
 private:
  const math::Dimension size;

  // We need 2 frames to write the changes each round
  Grid frame1;
  Grid frame2;

  // Keep pointers to the frames so we can easily swap them each round instead
  // of copying
  Grid* last_round = &frame1;
  Grid* next_round = &frame2;

  const CRGB color;
  const uint8_t pixel_height;

 public:
  Life(math::Dimension display_size, CRGB color, uint8_t pixel_height = 1)
      : Animation(),
        size{display_size.width, display_size.height / pixel_height},
        color{color},
        pixel_height{pixel_height},
        frame1{size},
        frame2{size} {}

  void SetCell(size_t x, size_t y, bool state = true) {
    if (x >= 0 && x < size.width && y >= 0 && y < size.height) {
      next_round->Cell(x, y) = state;
    }
  }

  void GoOneRound() {
    // swap last round with next round
    std::swap(last_round, next_round);

    // Calculate the next round based on the last one
    for (size_t x = 0; x < size.width; ++x) {
      for (size_t y = 0; y < size.height; ++y) {
        uint8_t neighborsAlive = 0;
        for (int i = -1; i <= 1; i++) {
          for (int j = -1; j <= 1; j++) {
            // don't count *this* cell
            if (i == 0 && j == 0) {
              continue;
            }

            // calculate neighbor cell indices
            size_t neighborStrip = (x + i + size.width) % size.width;
            size_t neighborLED = (y + j + size.height) % size.height;

            // count up the 'alive' neighbors in the last round
            if (last_round->Cell(neighborStrip, neighborLED)) {
              neighborsAlive++;
            }
          }
        }

        bool alive = last_round->Cell(x, y);
        if (neighborsAlive < 2) {
          alive = false;  // dead
        } else if (neighborsAlive > 3) {
          alive = false;  // dead
        } else if (neighborsAlive == 3) {
          alive = true;  // bring the dead to life!
        } else {
          // the old get older but nobody gets born here
        }

        next_round->Cell(x, y) = alive;
      }
    }
  }

  void Draw(display::Display* display) override {
    for (size_t x = 0; x < size.width; x++) {
      for (size_t y = 0; y < size.height; y++) {
        if (next_round->Cell(x, y)) {
          const size_t height = y * pixel_height;
          for (size_t height_offset = 0; height_offset < pixel_height;
               ++height_offset) {
            // display->BlendPixel(x, height + height_offset, color, .5);
			display->Pixel(x, height + height_offset) |= color;
          }
        }
      }
    }
  }

  void Randomize(const float density) { next_round->Randomize(density); }
};

}  // namespace animation
}  // namespace kss
