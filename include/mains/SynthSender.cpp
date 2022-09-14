// #include <Arduino.h>
// #include <FastLED.h>

// #include <memory>  // for shared_ptr

// #include "PinSetup.h"
// #include "audio/constants.h"           // for k*
// #include "audio/synth_sender.h"        // for RocketGame
// #include "controls/button.h"           // for Button
// #include "controls/dir_pad.h"          // for Inputs
// #include "controls/hardware/matrix.h"  // for controls::hardware::Matrix
// #include "serial/debug.h"              // for debug::*
// #include "serial/transmitter.h"        // for Transmitter

// kss::controls::hardware::Matrix controls;

// kss::audio::SynthSender* synth = new kss::audio::SynthSender(  //
//     controls.CreateButton(2, BUTTON_PIN_4),                    //
//     controls.CreateButton(2, BUTTON_PIN_3),                    //
//     controls.CreateButton(2, BUTTON_PIN_5),                    //
//     controls.CreateButton(2, BUTTON_PIN_2),                    //
//     controls.CreateButton(2, BUTTON_PIN_1),                    //
//     controls.CreateButton(2, BUTTON_PIN_0));                   //

// void setup() {
//   debug::Init();

//   debug::println((String) "ready 2 goooo");
// }

// void loop() {
//   //   debug::println("Loops brother");
//   controls.PollAll();
//   //   debug::println("Poll'd");
//   synth->checkButtonChange();
//   //   debug::println("Next Loop!");

//   // Emulate ~150 fps
//   delay(7);
// }
