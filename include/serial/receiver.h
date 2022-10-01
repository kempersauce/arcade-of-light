#pragma once

#include <HardwareSerial.h>  // for HardwareSerial

#include <queue>

#include "serial/constants.h"  // for serial::k*

namespace kss {
namespace serial {

class Receiver {
  std::queue<char*> outputQueue;

  char* inputBuffer;
  size_t ndx{0};
  bool recvInProgress{false};

  HardwareSerial* serial;

 public:
  Receiver(HardwareSerial* serial) : serial{serial} {
    inputBuffer = (char*)malloc(kMessageBufferSize);

    serial->begin(kBaudRate);
  }

  // TODO re-visit this: we allocate an oversized buffer
  // since some of the total message size includes start/stop chars
  // which are never included in the receiver buffer
  bool ReceiveMessages() {
    while (serial->available() > 0) {
      const char rc = serial->read();

      if (recvInProgress) {
        if (rc != kMessageEndMarker) {
          inputBuffer[ndx] = rc;
          ndx++;
          if (ndx >= kMessageBufferSize) {
            ndx = kMessageBufferSize - 1;
          }
        } else {
          inputBuffer[ndx] = '\0';  // terminate the string
          recvInProgress = false;
          ndx = 0;

          outputQueue.push(inputBuffer);
          inputBuffer = (char*)malloc(kMessageBufferSize);
        }
      }

      else if (rc == kMessageStartMarker) {
        recvInProgress = true;
      }
    }

    return HasMessages();
  }

  bool HasMessages() { return !outputQueue.empty(); }

  bool GetNextMessage(char* dest_buffer) {
    if (!outputQueue.empty()) {
      char* message = outputQueue.front();
      outputQueue.pop();

      strcpy(dest_buffer, message);
      free(message);
      return true;
    }

    return false;
  }
};

}  // namespace serial
}  // namespace kss
