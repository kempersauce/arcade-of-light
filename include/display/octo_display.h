#pragma once

#include <OctoWS2811.h>  // for octo-stuff
#include <pixeltypes.h>  // for CRGB

#include "display/display.h"  // for Display

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

 public:
  OctoDisplay(const uint8_t* pin_list, int* displayMemory)
      : Display({STRIP_COUNT, STRIP_LENGTH}),
        octo(size.y, displayMemory, drawingMemory, WS2811_RGB | WS2811_800kHz,
             size.x, pin_list) {
    octo.begin();
  }

  virtual ~OctoDisplay() = default;
  OctoDisplay(const OctoDisplay*) = delete;
  OctoDisplay* operator=(const OctoDisplay*) = delete;
  OctoDisplay(OctoDisplay*&) = delete;
  OctoDisplay* operator=(OctoDisplay*&) = delete;

  virtual inline CRGB& Pixel(size_t strip, size_t pixel) override {
    if (!CheckLocation(strip, pixel)) {
      return dummy_pixel;
    }
    return pixels[strip * size.y + pixel];
  }

  virtual void Show() override {
    for (int i = 0; i < total_pixel_count; ++i) {
      octo.setPixel(i, pixels[i].r, pixels[i].g, pixels[i].b);
    }
    octo.show();
  }
};

}  // namespace display
}  // namespace kss
