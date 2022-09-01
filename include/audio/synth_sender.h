#pragma once

#include <HardwareSerial.h>  // for HardwareSerial

#include "audio/constants.h"     // for k*
#include "serial/transmitter.h"  // for Transmitter
#include "controls/button.h"
#include "serial/debug.h"      // for debug::*


namespace kss {
namespace audio {

class SynthSender {
  serial::Transmitter transmitter;

  // Button time
  std::shared_ptr<controls::Button> up_btn;
  std::shared_ptr<controls::Button> down_btn;
  std::shared_ptr<controls::Button> left_btn;
  std::shared_ptr<controls::Button> right_btn;
  std::shared_ptr<controls::Button> a_btn;
  std::shared_ptr<controls::Button> b_btn;

  // Set up a message with the header info regarding audio channel and action
  inline const void InitMessage(char* buffer, char start_stop) {
    buffer[0] = start_stop;
    buffer[1] = '\0';
  }

 public:
  // Constructor: starts serial connection to audioSlave
  SynthSender(std::shared_ptr<controls::Button> up, 
  std::shared_ptr<controls::Button> down, 
  std::shared_ptr<controls::Button> left, 
  std::shared_ptr<controls::Button> right,
  std::shared_ptr<controls::Button> a,
  std::shared_ptr<controls::Button> b,
  HardwareSerial* serial = &Serial1) : transmitter{serial}, 
    up_btn{std::move(up)},
    down_btn{std::move(down)},
    left_btn{std::move(left)},
    right_btn{std::move(right)},
    a_btn{std::move(a)},
    b_btn{std::move(b)} {}

  // prepare input started message for synth
  const void StartInput(const char* inputName) {
    char msg[15];
    InitMessage(msg, kChannelActionPlay);
    strcat(msg, inputName);
    transmitter.Send(msg);
    debug::println((String) msg);
  }

  // prepare input stop message for synth
  const void StopInput(const char* inputName) {
    char msg[15];
    InitMessage(msg, kChannelActionStop);
    strcat(msg, inputName);
    transmitter.Send(msg);
    debug::println((String) msg);
  }

  // checks if any buttons have changed state
  const void checkButtonChange() {
    if(up_btn->IsDepressing()) {
      StartInput("up");
    }
    if(up_btn->IsReleasing()) {
      StopInput("up");
    }
    if(down_btn->IsDepressing()) {
      StartInput("down");
    }
    if(down_btn->IsReleasing()) {
      StopInput("down");
    }
    if(left_btn->IsDepressing()) {
      StartInput("left");
    }
    if(left_btn->IsReleasing()) {
      StopInput("left");
    }
    if(right_btn->IsDepressing()) {
      StartInput("right");
    }
    if(right_btn->IsReleasing()) {
      StopInput("right");
    }
    if(a_btn->IsDepressing()) {
      StartInput("a");
    }
    if(a_btn->IsReleasing()) {
      StopInput("a");
    }
    if(b_btn->IsDepressing()) {
      StartInput("b");
    }
    if(b_btn->IsReleasing()) {
      StopInput("b");
    }
  }
};

}  // namespace audio
}  // namespace kss
