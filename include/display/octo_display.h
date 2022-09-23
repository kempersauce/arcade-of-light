#pragma once

#include <OctoWS2811.h>  // for octo-stuff
#include <pixeltypes.h>  // for CRGB

#include "display/display.h"          // for Display
#include "display/octo/controller.h"  // for octo stuff

/*
OctoDisplay Class
holds the pixels and buffers for OctoWS2811 library
*/

namespace kss {
namespace display {

template <size_t STRIP_COUNT, size_t STRIP_LENGTH>
class OctoDisplay : public Display {
  static constexpr int total_pixel_count{STRIP_COUNT * STRIP_LENGTH};

  // These buffers need to be large enough for all the pixels.
  // The total number of pixels is "ledsPerStrip * numPins".
  // Each pixel needs 3 bytes, so multiply by 3.  An "int" is
  // 4 bytes, so divide by 4.  The array is created using "int"
  // so the compiler will align it to 32 bit memory.
  // DMAMEM int displayMemory[total_pixel_count * 3 / 4];
  int drawingMemory[total_pixel_count * 3 / 4];

  CRGB pixels[total_pixel_count];
  OctoWS2811 octo;
  CTeensy4Controller<GRB, WS2811_800kHz> controller;

 public:
  OctoDisplay(const uint8_t* pin_list, int* displayMemory)
      : Display({STRIP_COUNT, STRIP_LENGTH}),
        octo(size.y, displayMemory, drawingMemory, WS2811_RGB | WS2811_800kHz,
             size.x, pin_list),
        controller(&octo) {
    octo.begin();
    FastLED.addLeds(&controller, pixels, total_pixel_count);
  }
  virtual ~OctoDisplay() = default;
  OctoDisplay(const OctoDisplay*) = delete;
  OctoDisplay* operator=(const OctoDisplay*) = delete;
  OctoDisplay(OctoDisplay*&) = delete;
  OctoDisplay* operator=(OctoDisplay*&) = delete;

  virtual inline CRGB& Pixel(size_t strip, size_t pixel) override {
    CheckLocation(strip, pixel);
    return pixels[strip * size.y + pixel];
  }

  virtual void Show() override { FastLED.show(); }
};

}  // namespace display
}  // namespace kss
