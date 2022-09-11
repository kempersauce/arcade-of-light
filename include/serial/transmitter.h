#pragma once

#include <HardwareSerial.h>  // for HardwareSerial

#include <string>

#include "serial/constants.h"  // for serial::k*
#include "serial/debug.h"      // for Debug

namespace kss {
namespace serial {

class Transmitter {
 public:
  HardwareSerial* serial;

  Transmitter(HardwareSerial* serial) : serial{serial} {
    serial->begin(115200);
  }

  inline const void Send(const char* msg) { Send((String)msg); }

  const void Send(String msg) {
    const String finalMsg =
        (String)kMessageStartMarker + msg + kMessageEndMarker;
    if (finalMsg.length() >= kMessageBufferSize) {
      Debug("Transmission Error: message longer than buffer size (" + kMessageBufferSize + "): \"" + finalMsg + "\"");
    } else {
      serial->println(finalMsg);
      Debug("Transmitting: \"" + finalMsg + "\"");
    }
  }
};

}  // namespace serial
}  // namespace kss
