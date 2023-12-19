/*  OctoWS2811 Teensy4_PinList.ino - Demonstrate use of any pins
    http://www.pjrc.com/teensy/td_libs_OctoWS2811.html
  With Teensy 4.x, you can use any group of pins.  You are not limited
  to only 8 fixed pins as with Teensy 3.x.  This example shows how to
  use only 4 pins, which are the 4 pins of the Octo28 shield which do
  not conflict with the Audio shield.
  Required Connections
  --------------------
    pin 2:  LED Strip #1
    pin 14: LED strip #2
    pin 6:  LED strip #5
    pin 5:  LED strip #8
*/

#include <OctoWS2811.h>

// Any group of digital pins may be used
const int numPins = 20;
byte pinList[numPins] = {18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
                         28, 29, 30, 31, 32, 33, 34, 35, 36, 37};

const int ledsPerStrip = 280;

// These buffers need to be large enough for all the pixels.
// The total number of pixels is "ledsPerStrip * numPins".
// Each pixel needs 3 bytes, so multiply by 3.  An "int" is
// 4 bytes, so divide by 4.  The array is created using "int"
// so the compiler will align it to 32 bit memory.
const int bytesPerLED = 3;  // change to 4 if using RGBW
DMAMEM int displayMemory[ledsPerStrip * numPins * bytesPerLED / 4];
int drawingMemory[ledsPerStrip * numPins * bytesPerLED / 4];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config, numPins,
                pinList);

void setup() {
  leds.begin();
  leds.show();
}

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00
#define PINK 0xFF1088
#define ORANGE 0xE05800
#define WHITE 0xFFFFFF

// Less intense...
/*
#define RED    0x160000
#define GREEN  0x001600
#define BLUE   0x000016
#define YELLOW 0x101400
#define PINK   0x120009
#define ORANGE 0x100400
#define WHITE  0x101010
*/

void colorWipe(const int color, const uint32_t wait) {
  for (size_t i = 0; i < ledsPerStrip; i++) {
    for (size_t j = 0; j < numPins; i++) {
      leds.setPixel(j * ledsPerStrip + i, color);
      leds.show();
      delayMicroseconds(wait);
    }
  }
}

void loop() {
  const uint32_t microsec = 2 * 1000 * 1000 / leds.numPixels();  // change them all in 2 seconds

  // uncomment for voltage controlled speed
  // millisec = analogRead(A9) / 40;

  colorWipe(RED, microsec);
  colorWipe(GREEN, microsec);
  colorWipe(BLUE, microsec);
  colorWipe(YELLOW, microsec);
  colorWipe(PINK, microsec);
  colorWipe(ORANGE, microsec);
  colorWipe(WHITE, microsec);
}
