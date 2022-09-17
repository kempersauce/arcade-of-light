#pragma once

#include <HardwareSerial.h>  // for HardwareSerial

#include "audio/constants.h"        // for SynthAudioMessage
#include "controls/button.h"        // for Button
#include "serial/debug.h"           // for Debug
#include "serial/ez_transmitter.h"  // for Transmitter

namespace kss {
namespace audio {

namespace _synth_sender {

constexpr size_t button_array_size{4};
constexpr size_t transmitter_count{2};

}  // namespace _synth_sender
using namespace _synth_sender;

class SynthSender {
  // Button time
  controls::Button* btns[button_array_size];
  controls::Button* shift;

  size_t current_transmitter_index{0};
  serial::EZTransmitter<SynthAudioMessage> transmitters[transmitter_count];

 public:
  // Constructor: starts serial connection to audioSlave
  SynthSender(controls::Button* up, controls::Button* down,
              controls::Button* left, controls::Button* right,
              controls::Button* a, controls::Button* b)
      : btns{up, down, left, right},
        shift{a},
        transmitters{{&Serial1}, {&Serial2}} {}

  void Send(uint8_t channel, uint8_t action) {
    SynthAudioMessage msg;
    msg.action = action;
    msg.channel = channel;
    transmitters[current_transmitter_index].Send(msg);
    Debug("Sending on transmitter[" + current_transmitter_index + "]");
  }

  // prepare input started message for synth
  void StartInput(uint8_t channel) {
    Send(channel, kChannelActionPlay);
    Debug("Sent <PLay> on channel " + channel);
  }

  // prepare input stop message for synth
  void StopInput(uint8_t channel) {
    Send(channel, kChannelActionStop);
    Debug("Sent <STop> on channel " + channel);
  }

  void ShiftTo(size_t index) {
    Debug("Shifting to transmitter[" + index + "]");
    for (size_t i = 0; i < button_array_size; ++i) {
      if (btns[i]->IsPressed()) {
        StopInput(i);
      }
    }
    current_transmitter_index = index;
    for (size_t i = 0; i < button_array_size; ++i) {
      if (btns[i]->IsPressed()) {
        StartInput(i);
      }
    }
    Debug("Shifting to transmitter[" + index + "] ~FiN~");
  }

  // checks if any buttons have changed state
  void checkButtonChange() {
    // Shift to transmitter B
    if (shift->IsDepressing()) {
      ShiftTo(1);
    }

    // Shift to transmitter A
    if (shift->IsReleasing()) {
      ShiftTo(0);
    }

    // Run channels normally
    for (size_t i = 0; i < button_array_size; ++i) {
      if (btns[i]->IsDepressing()) {
        StartInput(i);
      }
      if (btns[i]->IsReleasing()) {
        StopInput(i);
      }
    }
  }
};

}  // namespace audio
}  // namespace kss
