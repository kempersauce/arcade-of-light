#pragma once

#include <HardwareSerial.h>  // for HardwareSerial

#include <string>

#include "serial/constants.h"  // for serial::k*
#include "serial/debug.h"      // for debug::*

namespace kss {
namespace serial {

class Transmitter {
 public:
  HardwareSerial* serial;

  Transmitter(HardwareSerial* serial = &Serial1) : serial{serial} {
    serial->begin(115200);
  }

  inline void Send(const String& msg) const { Send(msg.c_str()); }

  void Send(const char* msg) const {
    const String finalMsg =
        (String)kMessageStartMarker + msg + kMessageEndMarker;
    if (finalMsg.length() >= kMessageBufferSize) {
      debug::println(
          (String) "Transmission Error: message longer than buffer size (" +
          kMessageBufferSize + "): \"" + finalMsg + "\"");
    } else {
      serial->println(finalMsg);
      debug::println((String) "Transmitting: \"" + finalMsg + "\"");
    }
  }
};

}  // namespace serial
}  // namespace kss
