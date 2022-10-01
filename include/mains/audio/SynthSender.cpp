#include <Arduino.h>
#include <FastLED.h>

#include "audio/constants.h"           // for k*
#include "audio/synth_sender.h"        // for SynthSender
#include "controls/button.h"           // for Button
#include "controls/dir_pad.h"          // for Inputs
#include "controls/hardware/matrix.h"  // for controls::hardware::Matrix
#include "pins/pin_setup.h"            // for pins::*
#include "serial/debug.h"              // for Debug
#include "serial/hw_serials.h"         // for kHwSerials
#include "serial/transmitter.h"        // for Transmitter

using namespace kss;

controls::hardware::Matrix control_context;
audio::SynthSender* synths[4];

void setup() {
  Debug_init();
  pins::Init();

  for (size_t i = 0; i < 4; ++i) {
    synths[i] = new audio::SynthSender(
        control_context.CreateButton(pins::Controllers[i], pins::Buttons[5]),
        control_context.CreateButton(pins::Controllers[i], pins::Buttons[4]),
        control_context.CreateButton(pins::Controllers[i], pins::Buttons[3]),
        control_context.CreateButton(pins::Controllers[i], pins::Buttons[2]),
        control_context.CreateButton(pins::Controllers[i], pins::Buttons[1]),
        control_context.CreateButton(pins::Controllers[i], pins::Buttons[0]),
        serial::kHwSerials[i]);
  }

  Debug("ready 2 goooo");
}

void loop() {
  //   Debug("Loops brother");
  control_context.PollAll();
  //   Debug("Poll'd");
  for (auto synth : synths) {
    synth->checkButtonChange();
  }
  //   Debug("Next Loop!");

  // Emulate ~150 fps
  delay(7);
}
