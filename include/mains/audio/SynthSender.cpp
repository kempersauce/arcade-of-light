#include <Arduino.h>
#include <FastLED.h>

#include "PinSetup.h"                  // for pins::*
#include "audio/constants.h"           // for k*
#include "audio/synth_sender.h"        // for RocketGame
#include "controls/button.h"           // for Button
#include "controls/dir_pad.h"          // for Inputs
#include "controls/hardware/matrix.h"  // for controls::hardware::Matrix
#include "serial/debug.h"              // for Debug
#include "serial/transmitter.h"        // for Transmitter

using namespace kss;

controls::hardware::Matrix control_context;
audio::SynthSender* synth;

void setup() {
  Debug_init();
  pins::Init();

  synth = new kss::audio::SynthSender(
    // clang-format off
    control_context.CreateButton(pins::Controllers[0], pins::Buttons[4]),
    control_context.CreateButton(pins::Controllers[0], pins::Buttons[3]),
    control_context.CreateButton(pins::Controllers[0], pins::Buttons[5]),
    control_context.CreateButton(pins::Controllers[0], pins::Buttons[2]),
    control_context.CreateButton(pins::Controllers[0], pins::Buttons[1]),
    control_context.CreateButton(pins::Controllers[0], pins::Buttons[0])
    // clang-format on
  );

  Debug("ready 2 goooo");
}

void loop() {
  //   Debug("Loops brother");
  control_context.PollAll();
  //   Debug("Poll'd");
  synth->checkButtonChange();
  //   Debug("Next Loop!");

  // Emulate ~150 fps
  delay(7);
}
