// #include <Arduino.h>
// #include "controls/button.h"
// #include <vector>
// #include "test/five_strip.h"  // for FiveStripTest
// #include "display/five.h"  // for FiveDisplay

// using namespace kss;

// display::FiveDisplay* gameDisplay;
// test::FiveStripTest* test;

// std::vector<controls::Button> buttons;
// void setup()
// {
//     gameDisplay = new display::FiveDisplay();
//     test = new test::FiveStripTest(gameDisplay);
//     test->setup();
// 	Serial.begin(9600);
// 	for (int i = 0; i < 32; i++)
// 	{
// 		buttons.push_back(Button(i));
// 	}
//     //test->loop();
//     gameDisplay->Show();
// }

// void loop()
// {
//     for (int i = 0; i < gameDisplay->strip_length; i++)
//     {
//         gameDisplay->Pixel(0, i) = CRGB::Red;
//         gameDisplay->Pixel(1, i) = CRGB::Green;
//         gameDisplay->Pixel(2, i) = CRGB::Blue;
//         gameDisplay->Pixel(3, i) = CRGB::Yellow;
//         gameDisplay->Pixel(4, i) = CRGB::Violet;
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
//     gameDisplay->Show();

// }
