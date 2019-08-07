#include <Arduino.h>
#include <FastLED.h>
#include <Display.h>
#include <H2HDisplay.h>
#include <Game.h>

#define BRIGHTNESS 30
#define delayVal 0

class NoiseGame : Game
{
    public:
        NoiseGame(Display* gameDisplay)
            : Game(gameDisplay)
        {
        }

        void setup()
        {
            background = (Animation*)new Noise();
            FastLED.setBrightness(BRIGHTNESS);
        }

        void loop()
        {
            background->draw(display);
            FastLED.delay(delayVal);
            FastLED.show();
        }
};

Game* NoiseGame;



void setup() {
    H2HDisplay* NoiseGameDisplay = new H2HDisplay();
    NoiseGame = (Game*)new NoiseGame(NoiseGameDisplay);
    NoiseGame->setup();
}

void loop() {
    NoiseGame->loop();
}
// #include <FastLED.h>
// #include <Arduino.h>
//
// //initialize displays the bad ways
//
// #define NUM_STRIPS 8
// #define NUM_LEDS 121
//
// #define H2H_LED_PIN_0 20
// #define H2H_LED_PIN_1 17
// #define H2H_LED_PIN_2 16
// #define H2H_LED_PIN_3 39
// #define H2H_LED_PIN_4 38
// #define H2H_LED_PIN_5 37
// #define H2H_LED_PIN_6 36
// #define H2H_LED_PIN_7 35
//
//
//
//
// //
// // Mark's xy coordinate mapping code.  See the XYMatrix for more information on it.
// //
//
// // The leds
// CRGB leds[NUM_STRIPS][NUM_LEDS];
//
// // The 16bit version of our coordinates
// static uint16_t x;
// static uint16_t y;
// static uint16_t z;
//
// // We're using the x/y dimensions to map to the x/y pixels on the matrix.  We'll
// // use the z-axis for "time".  speed determines how fast time moves forward.  Try
// // 1 for a very slow moving effect, or 60 for something that ends up looking like
// // water.
// // uint16_t speed = 1; // almost looks like a painting, moves very slowly
// uint16_t speed = 20; // a nice starting speed, mixes well with a scale of 100
// // uint16_t speed = 33;
// // uint16_t speed = 100; // wicked fast!
//
// // Scale determines how far apart the pixels in our noise matrix are.  Try
// // changing these values around to see how it affects the motion of the display.  The
// // higher the value of scale, the more "zoomed out" the noise iwll be.  A value
// // of 1 will be so zoomed in, you'll mostly see solid colors.
//
// // uint16_t scale = 1; // mostly just solid colors
// // uint16_t scale = 4011; // very zoomed out and shimmery
// uint16_t scale = 1024;
//
// // This is the array that we keep our computed noise values in
// uint8_t noise[NUM_STRIPS][NUM_LEDS];
//
// void setup() {
//   // uncomment the following lines if you want to see FPS count information
//   // Serial.begin(38400);
//   // Serial.println("resetting!");
//   delay(3000);
//   FastLED.addLeds<WS2812B, H2H_LED_PIN_7, GRB>(leds[7], NUM_LEDS);
//   FastLED.addLeds<WS2812B, H2H_LED_PIN_6, GRB>(leds[6], NUM_LEDS);
//   FastLED.addLeds<WS2812B, H2H_LED_PIN_5, GRB>(leds[5], NUM_LEDS);
//   FastLED.addLeds<WS2812B, H2H_LED_PIN_4, GRB>(leds[4], NUM_LEDS);
//   FastLED.addLeds<WS2812B, H2H_LED_PIN_3, GRB>(leds[3], NUM_LEDS);
//   FastLED.addLeds<WS2812B, H2H_LED_PIN_2, GRB>(leds[2], NUM_LEDS);
//   FastLED.addLeds<WS2812B, H2H_LED_PIN_1, GRB>(leds[1], NUM_LEDS);
//   FastLED.addLeds<WS2812B, H2H_LED_PIN_0, GRB>(leds[0], NUM_LEDS);
//   LEDS.setBrightness(96);
//
//   // Initialize our coordinates to some random values
//   x = random16();
//   y = random16();
//   z = random16();
// }
//
// // Fill the x/y array of 8-bit noise values using the inoise8 function.
// void fillnoise8() {
//   for(int i = 0; i < NUM_STRIPS; i++) {
//     int ioffset = scale * i;
//     for(int j = 0; j < NUM_LEDS; j++) {
//       int joffset = scale * j;
//       noise[i][j] = inoise8(x + ioffset,y + joffset,z);
//     }
//   }
//   z += speed;
// }
//
//
// void loop() {
//   static uint8_t ihue=0;
//   fillnoise8();
//   for(int i = 0; i < NUM_STRIPS; i++) {
//     for(int j = 0; j < NUM_LEDS; j++) {
//       // We use the value at the (i,j) coordinate in the noise
//       // array for our brightness, and the flipped value from (j,i)
//       // for our pixel's hue.
//       //leds[i][j] = CHSV(noise[j][i],255,noise[i][j]);
//       leds[i][j] = CHSV(ihue + (noise[j][i]>>2),255,noise[i][j]);
//       // You can also explore other ways to constrain the hue used, like below
//       // leds[XY(i,j)] = CHSV(ihue + (noise[j][i]>>2),255,noise[i][j]);
//     }
//   }
//   ihue+=1;
//
//   LEDS.show();
//   // delay(10);
// }
