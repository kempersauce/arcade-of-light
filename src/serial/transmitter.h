#pragma once

#include <HardwareSerial.h>  // for HardwareSerial

#include <string>

#include "serial/constants.h"  // for serial::k*
#include "serial/debug.h"      // for Debug

namespace kss {
namespace serial {

class Transmitter {
  HardwareSerial* serial;

 public:
  Transmitter(HardwareSerial* serial) : serial{serial} {
    serial->begin(kBaudRate);
  }

  inline void Send(const char* msg) const { Send((String)msg); }

  void Send(String msg) const {
    const String finalMsg =
        (String)kMessageStartMarker + msg + kMessageEndMarker;
    if (finalMsg.length() >= kMessageBufferSize) {
      Debug("Transmission Error: message longer than buffer size (" +
            kMessageBufferSize + "): \"" + finalMsg + "\"");
    } else {
      serial->flush();  // wait for any previous transmissions still being sent
      serial->println(finalMsg);
      Debug("Transmitting: \"" + finalMsg + "\"");
    }
  }
};

}  // namespace serial
}  // namespace kss
