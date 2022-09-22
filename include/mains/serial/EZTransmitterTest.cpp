#include <HardwareSerial.h>  // for HardwareSerial

#include "serial/debug.h"           // for Debug
#include "serial/ez_transmitter.h"  // for EZTransmitter
#include "time/now.h"               // for Now

using namespace kss::serial;

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

constexpr size_t transmitter_count{8};

EZTransmitter<SEND_DATA_STRUCTURE> transmitters[transmitter_count]{
    {&Serial1}, {&Serial2}, {&Serial3}, {&Serial4},
    {&Serial5}, {&Serial6}, {&Serial7}, {&Serial8}};

void setup() { Debug_init(); }

void loop() {
  SEND_DATA_STRUCTURE msg;
  msg.test_uint32 = time::Now();
  static uint8_t message_no = 0;
  msg.test_uint8 = message_no++;
  for (size_t i = 0; i < transmitter_count; ++i) {
    const String serial_label = (String) "Serial" + (String)(i + 1);
    strcpy(msg.test_str, serial_label.c_str());
    Debug(serial_label + " sending msg[" + msg.test_uint8 +
          "] (t=" + msg.test_uint32 + ") \"" + msg.test_str + "\"");
    transmitters[i].Send(msg);
  }
  delay(100);
}
