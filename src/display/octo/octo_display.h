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

 protected:
  // pixels initializes to all zeros
  CRGB pixels[total_pixel_count] = {};
  bool is_grb[STRIP_COUNT];

 public:
  OctoDisplay(const uint8_t* pin_list, int* displayMemory,
              math::Vector2D<float> grid_scale, size_t instructo_count = 0)
      : Display({STRIP_COUNT, STRIP_LENGTH}, grid_scale),
        octo{size.y, displayMemory, drawingMemory, WS2811_RGB | WS2811_800kHz,
             size.x, pin_list} {
    // Set strips to GRB, except instructos are RGB
    for (size_t strip = 0; strip < STRIP_COUNT; ++strip) {
      is_grb[strip] = strip < STRIP_COUNT - instructo_count;
    }

    octo.begin();
  }

  virtual ~OctoDisplay() = default;

  // Delete copy constructor & assignment operator, force them to make their own
  OctoDisplay(const OctoDisplay*) = delete;
  OctoDisplay* operator=(const OctoDisplay*) = delete;
  OctoDisplay(OctoDisplay*&) = delete;
  OctoDisplay* operator=(OctoDisplay*&) = delete;

  virtual CRGB& Pixel(size_t strip, size_t pixel) override {
    if (!CheckLocation(strip, pixel)) {
      return dummy_pixel;
    }
    return pixels[strip * size.y + pixel];
  }

 private:
  inline void ShowStripRGB(const size_t strip_no) {
    const size_t start{strip_no * STRIP_LENGTH};
    const size_t stop{(strip_no + 1) * STRIP_LENGTH};
    for (size_t i = start; i < stop; ++i) {
      octo.setPixel(i, pixels[i].g, pixels[i].r, pixels[i].b);
    }
  }

  inline void ShowStripGRB(const size_t strip_no) {
    const size_t start{strip_no * STRIP_LENGTH};
    const size_t stop{(strip_no + 1) * STRIP_LENGTH};
    for (size_t i = start; i < stop; ++i) {
      octo.setPixel(i, pixels[i].r, pixels[i].g, pixels[i].b);
    }
  }

 public:
  virtual void Show() override {
    for (size_t strip = 0; strip < STRIP_COUNT; ++strip) {
      if (is_grb[strip]) {
        ShowStripGRB(strip);
      } else {
        ShowStripRGB(strip);
      }
    }

    // Fire them bits down the tube
    octo.show();
  }
};

}  // namespace octo
}  // namespace display
}  // namespace kss
