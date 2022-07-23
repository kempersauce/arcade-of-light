
#include <queue>

using namespace std;

class KemperSerialReceiver {
  queue<char *> outputQueue;

 public:
  const static byte numChars = 32;

  // char receivedChars[numChars];
  char *inputBuffer;

  const HardwareSerial *serial;

  int led;
  int mostRecentUnreadMessage;
  int newestMessage;

  KemperSerialReceiver(const HardwareSerial *serialRef) {
    serial = serialRef;
    inputBuffer = (char *)malloc(numChars);

    serial->begin(9600);

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
