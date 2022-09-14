#include <HardwareSerial.h>  // for HardwareSerial

#include "serial/debug.h"           // for Debug
#include "serial/ez_transmitter.h"  // for EZTransmitter

using namespace kss::serial;

const String test_msg{"0123456789"};

struct SEND_DATA_STRUCTURE {
  // put your variable definitions here for the data you want to send
  // THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  uint32_t test_uint32 = 420000;
  uint16_t test_uint16 = 1337;
  uint8_t test_uint8 = 69;
  float test_float = 0.666;
  bool test_bool = true;
  char test_char = 'B';
  char test_str[20];
};

EZTransmitter<SEND_DATA_STRUCTURE> transmitter{&Serial1};

void setup() { Debug_init(); }

void loop() {
  SEND_DATA_STRUCTURE msg;
  msg.test_uint32 = millis();
  static uint8_t message_no = 0;
  msg.test_uint8 = message_no++;
  strcpy(msg.test_str, test_msg.c_str());
  Debug("Sending msg[" + msg.test_uint8 + "] (t=" + msg.test_uint32 + ") \"" +
        msg.test_str + "\"");
  transmitter.Send(msg);
}
