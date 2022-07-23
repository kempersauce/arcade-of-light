#pragma once

#include <Constants.h>

#include "display/display.h"  // for Display

/*
Display Class
holds the strips
*/
class RocketDisplay : public Display {
 public:
  RocketDisplay() : Display(3, 300) {
    FastLED.addLeds<WS2812B, 20, GRB>(strips[0], lengthStrips);
    FastLED.addLeds<WS2812B, 17, GRB>(strips[1], lengthStrips);
    FastLED.addLeds<WS2812B, 16, GRB>(strips[2], lengthStrips);
  }
};
