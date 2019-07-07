#include <Arduino.h>
#include <FastLED.h>
#define PIN 35   // OUTPUT pin WS28112b LED Strip is attached to TODO: Rename to LED_PIN
#define NUM_LEDS 300 // number of LEDs per strip TODO: Rename to NUM_LEDS
#define debounceTime 200 // keep those button inputs clean
#define delayval 25 //controls the "speed" of the player dot
#define animationDelay 0 //controls the speed of the win animation
#define brightness 25

//map<string, CRGB> colorPalette = new map<string, CRGB>();
//colorPalette["red"] = CHSV(69,69,69);


CRGB rainbows[14] = {
  CRGB::Red,
  CRGB::Orange,
  CRGB::Yellow,
  CRGB::Green,
  CRGB::Blue,
  CRGB::Indigo,
  CRGB::Violet,
  CRGB::Red,
  CRGB::Orange,
  CRGB::Yellow,
  CRGB::Green,
  CRGB::Blue,
  CRGB::Indigo,
  CRGB::Violet
};
int iterator = 0;

CRGB leds[NUM_LEDS];
void setup() {
  delay(10000);
  FastLED.addLeds<WS2812B, PIN>(leds, NUM_LEDS);
  FastLED.addLeds<WS2812B, (PIN + 1)>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
}
void loop(){
    for (int i=1; i < NUM_LEDS ; i++)
    {
        leds[i] = rainbows[(i%7)+iterator];
    }
    if (iterator < 6)
    {
        iterator++;
    }
    else
    {
        iterator = 0;
    }
    FastLED.show();
    delay(delayval);
}
