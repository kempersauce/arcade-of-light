#pragma once

#include <queue>
#include <string>

namespace kss {
namespace serial {

class Transmitter {
 public:
  const HardwareSerial *serial;
  const static byte numChars = 32;

  Transmitter(const HardwareSerial *serialRef) {
    serial = serialRef;
    serial->begin(9600);
  }

  void sendMessage(String msg) {
    int msgLength = msg.length();
    {
      if (msgLength > numChars) {
        return;
      } else {
        String finalMsg = "<" + msg + ">";
        serial->print(finalMsg);
      }
    }
  }
};

Transmitter Transmitter5(&Serial5);

}  // namespace serial
}  // namespace kss
