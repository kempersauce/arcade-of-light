// #include <Arduino.h>
// #include <FastLED.h>
// #include <memory>  // for shared_ptr
// #include "audio/synth_sender.h"  // for RocketGame
// #include "controls/hardware/simple.h"  // for controls::hardware::Simple
// #include "controls/button.h"
// #include "PinSetup.h"

// #include "audio/constants.h"     // for k*
// #include "serial/transmitter.h"  // for Transmitter
// #include "controls/dir_pad.h"    // for Inputs
// #include "serial/debug.h"      // for debug::*


// kss::controls::hardware::Simple controls;

// kss::audio::SynthSender* synth = new kss::audio::SynthSender(
//         controls.CreateButton(BUTTON_PIN_4),
//         controls.CreateButton(BUTTON_PIN_3),
//         controls.CreateButton(BUTTON_PIN_5),
//         controls.CreateButton(BUTTON_PIN_2),
//         controls.CreateButton(BUTTON_PIN_1),
//         controls.CreateButton(BUTTON_PIN_0));

// void setup()
// {

//     Serial.begin(115200);

//     debug::println((String) "ready 2 goooo");

// }

// void loop()
// {
//     debug::println("Loops brother");
//     controls.PollAll();
//     debug::println("Poll'd");
//     synth->checkButtonChange();
//     debug::println("Next Loop!");
// }
