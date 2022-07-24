#pragma once

#include <queue>
#include <string>

class KemperSerialTransmitter {
 public:
  const HardwareSerial *serial;
  const static byte numChars = 32;

  KemperSerialTransmitter(const HardwareSerial *serialRef) {
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

KemperSerialTransmitter Transmitter5(&Serial5);
