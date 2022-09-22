#pragma once

#include <FastLED.h>  // for CRGB

#include "animation/single_color_background.h"  // for SingleColorBG
#include "display/display.h"                    // for Display
#include "games/game.h"                         // for Game

namespace kss {
namespace test {

// Test for Directional Pad
class FiveStripTest : public games::Game {
 public:
  animation::SingleColorBG* backgroundColor;

  FiveStripTest(display::Display* gameDisplay) : Game(gameDisplay) {}

  void setStrips() {
    // debug which strip is which
    for (size_t i = 0; i < display->size.y; i++) {
      display->Pixel(0, i) = CRGB::Red;
      display->Pixel(1, i) = CRGB::Green;
      display->Pixel(2, i) = CRGB::Blue;
      display->Pixel(3, i) = CRGB::Yellow;
      display->Pixel(4, i) = CRGB::Violet;
    }
  }

  void setup() override { setStrips(); }

  void loop(const uint32_t now = millis()) override { setStrips(); }
};

}  // namespace test
}  // namespace kss
