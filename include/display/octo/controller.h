#include <Arduino.h>
#include <FastLED.h>
#include <OctoWS2811.h>

template <EOrder RGB_ORDER = GRB, uint8_t CHIP = WS2811_800kHz>
class CTeensy4Controller : public CPixelLEDController<RGB_ORDER, 8, 0xFF> {
  OctoWS2811 *pocto;

 public:
  CTeensy4Controller(OctoWS2811 *_pocto) : pocto(_pocto){};

  virtual void init() {}
  virtual void showPixels(PixelController<RGB_ORDER, 8, 0xFF> &pixels) {
    uint32_t i = 0;
    while (pixels.has(1)) {
      uint8_t r = pixels.loadAndScale0();
      uint8_t g = pixels.loadAndScale1();
      uint8_t b = pixels.loadAndScale2();
      pocto->setPixel(i++, g, r, b);  // manual hack whatever
      pixels.stepDithering();
      pixels.advanceData();
    }

    pocto->show();
  }
};