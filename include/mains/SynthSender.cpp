#include <Arduino.h>
#include <FastLED.h>

#include <memory>  // for shared_ptr

#include "PinSetup.h"
#include "audio/constants.h"           // for k*
#include "audio/synth_sender.h"        // for RocketGame
#include "controls/button.h"           // for Button
#include "controls/dir_pad.h"          // for Inputs
#include "controls/hardware/matrix.h"  // for controls::hardware::Matrix
#include "serial/debug.h"              // for Debug
#include "serial/transmitter.h"        // for Transmitter

kss::controls::hardware::Matrix controls;

kss::audio::SynthSender* synth = new kss::audio::SynthSender(
    // clang-format off
    controls.CreateButton(2, BUTTON_PIN_4),
    controls.CreateButton(2, BUTTON_PIN_3),
    controls.CreateButton(2, BUTTON_PIN_5),
    controls.CreateButton(2, BUTTON_PIN_2),
    controls.CreateButton(2, BUTTON_PIN_1),
    controls.CreateButton(2, BUTTON_PIN_0)
    // clang-format on
);

void setup() {
  Debug_init();

  // Get the controls poll'd up to start clean
  controls.PollAll();
  controls.PollAll();
  Debug("ready 2 goooo");
}

void loop() {
  //   Debug("Loops brother");
  controls.PollAll();
  //   Debug("Poll'd");
  synth->checkButtonChange();
  //   Debug("Next Loop!");

  // Emulate ~150 fps
  delay(7);
}
