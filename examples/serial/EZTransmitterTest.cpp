#include <Arduino.h>
#include <HardwareSerial.h>  // for HardwareSerial
#include <SPI.h>
#include <Wire.h>

#include "serial/debug.h"           // for Debug
#include "serial/ez_transmitter.h"  // for EZTransmitter
#include "serial/hw_serials.h"      // for kHwSerials
#include "time/now.h"               // for Now

using namespace kss;
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

EZTransmitter<SEND_DATA_STRUCTURE> transmitters[kHwSerialCount]{
    // clang-format off
    {kHwSerials[0]},
    {kHwSerials[1]},
    {kHwSerials[2]},
    {kHwSerials[3]},
    {kHwSerials[4]},
    {kHwSerials[5]}

#if defined(ARDUINO_TEENSY41) || defined(ARDUINO_TEENSY40)
    ,{kHwSerials[6]}
#endif

#if defined(ARDUINO_TEENSY41)
    ,{kHwSerials[7]}
#endif
    // clang-format on
};

void setup() { Debug_init(); }

void loop() {
  SEND_DATA_STRUCTURE msg;
  msg.test_uint32 = time::Now();
  static uint8_t message_no = 0;
  msg.test_uint8 = message_no++;
  for (size_t i = 0; i < kHwSerialCount; ++i) {
    const String serial_label = (String) "Serial" + (String)(i + 1);
    strcpy(msg.test_str, serial_label.c_str());
    Debug(serial_label + " sending msg[" + msg.test_uint8 +
          "] (t=" + msg.test_uint32 + ") \"" + msg.test_str + "\"");
    transmitters[i].Send(msg);
  }
  delay(100);
}
