#pragma once

#include <HardwareSerial.h>  // for HardwareSerial

#include "audio/constants.h"  // for k*
#include "controls/button.h"
#include "serial/debug.h"        // for debug::*
#include "serial/transmitter.h"  // for Transmitter

namespace kss {
namespace audio {

class SynthSender {
  // Button time
  controls::Button* up_btn;
  controls::Button* down_btn;
  controls::Button* left_btn;
  controls::Button* right_btn;
  controls::Button* a_btn;
  controls::Button* b_btn;

  serial::Transmitter transmitter;

  // Set up a message with the header info regarding audio channel and action
  inline const void InitMessage(char* buffer, char start_stop) {
    buffer[0] = start_stop;
    buffer[1] = '\0';
  }

 public:
  // Constructor: starts serial connection to audioSlave
  SynthSender(controls::Button* up, controls::Button* down,
              controls::Button* left, controls::Button* right,
              controls::Button* a, controls::Button* b,
              HardwareSerial* serial = &Serial1)
      : up_btn{up},
        down_btn{down},
        left_btn{left},
        right_btn{right},
        a_btn{a},
        b_btn{b},
        transmitter{serial} {}

  // prepare input started message for synth
  const void StartInput(const char* inputName) {
    char msg[15];
    InitMessage(msg, kChannelActionPlay);
    strcat(msg, inputName);
    transmitter.Send(msg);
    debug::println((String)msg);
  }

  // prepare input stop message for synth
  const void StopInput(const char* inputName) {
    char msg[15];
    InitMessage(msg, kChannelActionStop);
    strcat(msg, inputName);
    transmitter.Send(msg);
    debug::println((String)msg);
  }

  // checks if any buttons have changed state
  const void checkButtonChange() {
    if (up_btn->IsDepressing()) {
      StartInput("up");
    }
    if (up_btn->IsReleasing()) {
      StopInput("up");
    }
    if (down_btn->IsDepressing()) {
      StartInput("down");
    }
    if (down_btn->IsReleasing()) {
      StopInput("down");
    }
    if (left_btn->IsDepressing()) {
      StartInput("left");
    }
    if (left_btn->IsReleasing()) {
      StopInput("left");
    }
    if (right_btn->IsDepressing()) {
      StartInput("right");
    }
    if (right_btn->IsReleasing()) {
      StopInput("right");
    }
    if (a_btn->IsDepressing()) {
      StartInput("a");
    }
    if (a_btn->IsReleasing()) {
      StopInput("a");
    }
    if (b_btn->IsDepressing()) {
      StartInput("b");
    }
    if (b_btn->IsReleasing()) {
      StopInput("b");
    }
  }
};

}  // namespace audio
}  // namespace kss
