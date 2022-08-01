// #include <Arduino.h>
// #include "controls/button.h"
// #include <vector>
// #include "test/five_strip.h"  // for FiveStripTest
// #include "display/five.h"  // for FiveDisplay

// using namespace kss;

// display::FiveDisplay* display;
// test::FiveStripTest* test;

// std::vector<controls::Button> buttons;
// void setup()
// {
//     display = new display::FiveDisplay();
//     test = new test::FiveStripTest(display);
//     test->setup();
// 	Serial.begin(9600);
// 	for (int i = 0; i < 32; i++)
// 	{
// 		buttons.push_back(Button(i));
// 	}
//     //test->loop();
//     FastLED.show();
// }

// void loop()
// {
//     for (int i = 0; i < display->strip_length; i++)
//     {
//         display->Pixel(0, i) = CRGB::Red;
//         display->Pixel(1, i) = CRGB::Green;
//         display->Pixel(2, i) = CRGB::Blue;
//         display->Pixel(3, i) = CRGB::Yellow;
//         display->Pixel(4, i) = CRGB::Violet;
//     }

// 	for (int i = 0; i < buttons.size(); i++)
// 	{
// 		buttons[i].poll();
// 		if (buttons[i].IsDepressing())
// 		{
// 			Serial.println(i);
// 		}
// 	}
// 	delay(1000);
//     test->loop();
//     FastLED.show();

// }
