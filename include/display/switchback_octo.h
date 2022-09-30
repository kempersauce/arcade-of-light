#pragma once

#include <OctoWS2811.h>  // for octo-stuff
#include <pixeltypes.h>  // for CRGB

#include "display/display.h"          // for Display
#include "display/octo/controller.h"  // for octo stuff
#include "serial/debug.h"             // for Debug

namespace kss {
namespace display {

// TODO this should be implemented by inheriting OctoDisplay
// BUT then we would need to make number of pins a parameter for that
template <size_t row_count, size_t column_count>
class SwitchbackOctoDisplay : public Display {
  uint8_t pin_list[1];
  static constexpr int total_pixel_count{row_count * column_count};

  // These buffers need to be large enough for all the pixels.
  // The total number of pixels is "ledsPerStrip * numPins".
  // Each pixel needs 3 bytes, so multiply by 3.  An "int" is
  // 4 bytes, so divide by 4.  The array is created using "int"
  // so the compiler will align it to 32 bit memory.
  // DMAMEM int displayMemory[total_pixel_count * 3 / 4];
  int drawingMemory[total_pixel_count * 3 / 4];

  CRGB pixels[total_pixel_count];
  OctoWS2811 octo;
  CTeensy4Controller<RGB, WS2811_800kHz> controller;

 public:
  SwitchbackOctoDisplay(const uint8_t pin, int* displayMemory)
      : Display({row_count, column_count}),
        pin_list{pin},
        octo(total_pixel_count, displayMemory, drawingMemory,
             WS2811_RGB | WS2811_800kHz, 1,
             pin_list),  // this works?
        controller(&octo) {
    octo.begin();
    FastLED.addLeds(&controller, pixels, size.y * size.x);
  }
  virtual ~SwitchbackOctoDisplay() = default;
  SwitchbackOctoDisplay(const SwitchbackOctoDisplay*) = delete;
  SwitchbackOctoDisplay* operator=(const SwitchbackOctoDisplay*) = delete;
  SwitchbackOctoDisplay(SwitchbackOctoDisplay*&) = delete;
  SwitchbackOctoDisplay* operator=(SwitchbackOctoDisplay*&) = delete;

 public:
  virtual inline CRGB& Pixel(size_t x, size_t y) override {
    if (!CheckLocation(x, y)) {
		return dummy_pixel;
	}

    if (y % 2 == 1) {
      x = size.x - x - 1;
    }

    return pixels[y * size.x + x];
  }

  virtual void Show() override { FastLED.show(); }
};

}  // namespace display
}  // namespace kss
