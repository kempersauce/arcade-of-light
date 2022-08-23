#pragma once

#include <HardwareSerial.h>  // for HardwareSerial

#include <queue>

namespace kss {
namespace serial {

class Receiver {
  std::queue<char *> outputQueue;

 public:
  const static size_t numChars = 32;

  // char receivedChars[numChars];
  char *inputBuffer;

  HardwareSerial *serial;

  int led;
  int mostRecentUnreadMessage;
  int newestMessage;

  Receiver(HardwareSerial *serial) : serial{serial} {
    inputBuffer = (char *)malloc(numChars);

    serial->begin(115200);

    led = 13;  // TODO get rid of test output led code
    pinMode(led, OUTPUT);
    Serial.print("making a serial");
  }

 public:
  bool recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (serial->available() > 0) {
      rc = serial->read();
      // Serial.println(rc);//<--prints raw input stream to serial interface,
      // use for bugtesting

      if (recvInProgress == true) {
        if (rc != endMarker) {
          inputBuffer[ndx] = rc;
          ndx++;
          if (ndx >= numChars) {
            ndx = numChars - 1;
          }
        } else {
          inputBuffer[ndx] = '\0';  // terminate the string
          recvInProgress = false;
          ndx = 0;

          outputQueue.push(inputBuffer);
          inputBuffer = (char *)malloc(numChars);
        }
      }

      else if (rc == startMarker) {
        recvInProgress = true;
      }
    }

    return hasMessages();
  }

  bool hasMessages() { return !outputQueue.empty(); }

  bool getNextMessage(char *readLocation) {
    bool readMessage = false;

    if (!outputQueue.empty()) {
      readMessage = true;
      char *messageLocation = outputQueue.front();
      outputQueue.pop();

      strcpy(readLocation, messageLocation);
      free(messageLocation);
    }

    return readMessage;
  }
};

}  // namespace serial
}  // namespace kss
