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
namespace octo {

template <size_t STRIP_COUNT, size_t STRIP_LENGTH>
class OctoDisplay : public Display {
  static constexpr size_t total_pixel_count{STRIP_COUNT * STRIP_LENGTH};

  // These buffers need to be large enough for all the pixels.
  // The total number of pixels is "ledsPerStrip * numPins".
  // Each pixel needs 3 bytes, so multiply by 3.  An "int" is
  // 4 bytes, so divide by 4.  The array is created using "int"
  // so the compiler will align it to 32 bit memory.
  // DMAMEM int displayMemory[total_pixel_count * 3 / 4];
  int drawingMemory[total_pixel_count * 3 / 4];

  OctoWS2811 octo;
  const size_t front_pixels_in_grb;

 protected:
  // pixels initializes to all zeros
  CRGB pixels[total_pixel_count] = {};

 public:
  OctoDisplay(const uint8_t* pin_list, int* displayMemory,
              math::Vector2D<float> grid_scale, size_t end_pins_in_rgb = 0)
      : Display({STRIP_COUNT, STRIP_LENGTH}, grid_scale),
        octo{size.y, displayMemory, drawingMemory, WS2811_RGB | WS2811_800kHz,
             size.x, pin_list},
        front_pixels_in_grb{total_pixel_count -
                            end_pins_in_rgb * STRIP_LENGTH} {
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
    // Main display is GRB
    for (size_t i = 0; i < front_pixels_in_grb; ++i) {
      octo.setPixel(i, pixels[i].r, pixels[i].g, pixels[i].b);
    }

    // Instructos are RGB
    for (size_t i = front_pixels_in_grb; i < total_pixel_count; ++i) {
      octo.setPixel(i, pixels[i].g, pixels[i].r, pixels[i].b);
    }

    // Fire them bits down the tube
    octo.show();
  }
};

}  // namespace octo
}  // namespace display
}  // namespace kss
