#pragma once

#include <Constants.h>
#include "display/display.h"  // for Display

/*
Display Class
holds the strips
*/
class H2HDisplay : public Display {
 public:
  H2HDisplay() : Display(8, 214) {
    FastLED.addLeds<WS2812B, H2H_LED_PIN_7, GRB>(strips[7], lengthStrips);
    FastLED.addLeds<WS2812B, H2H_LED_PIN_6, GRB>(strips[6], lengthStrips);
    FastLED.addLeds<WS2812B, H2H_LED_PIN_5, GRB>(strips[5], lengthStrips);
    FastLED.addLeds<WS2812B, H2H_LED_PIN_4, GRB>(strips[4], lengthStrips);
    FastLED.addLeds<WS2812B, H2H_LED_PIN_3, GRB>(strips[3], lengthStrips);
    FastLED.addLeds<WS2812B, H2H_LED_PIN_2, GRB>(strips[2], lengthStrips);
    FastLED.addLeds<WS2812B, H2H_LED_PIN_1, GRB>(strips[1], lengthStrips);
    FastLED.addLeds<WS2812B, H2H_LED_PIN_0, GRB>(strips[0], lengthStrips);
  }
};
