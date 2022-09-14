#include <HardwareSerial.h>  // for HardwareSerial

#include "serial/debug.h"        // for Debug
#include "serial/ez_receiver.h"  // for Receiver

using namespace kss::serial;

struct SEND_DATA_STRUCTURE {
  // put your variable definitions here for the data you want to send
  // THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  uint32_t test_uint32;
  uint16_t test_uint16;
  uint8_t test_uint8;
  float test_float;
  bool test_bool;
  char test_char;
  char test_str[20];
};

EZReceiver<SEND_DATA_STRUCTURE> receiver{&Serial1};

void setup() { Debug_init(); }

void loop() {
  if (receiver.ReceiveMessages()) {
    SEND_DATA_STRUCTURE msg;
    while (receiver.GetNextMessage(msg)) {
      Debug("Message[" + msg.test_uint8 + "]: \"" + msg.test_str +
            "\" t=" + msg.test_uint32);
    }
  }
}
