#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "pins/pin_setup.h"      // for pins::Init
#include "serial/debug.h"        // for Debug
#include "serial/transmitter.h"  // for Transmitter

using namespace kss;
using namespace kss::serial;

constexpr size_t transmitter_count{8};

Transmitter transmitters_h[transmitter_count]{
    {&Serial1}, {&Serial2}, {&Serial3}, {&Serial4},
    {&Serial5}, {&Serial6}, {&Serial7}, {&Serial8}};

void setup() {
  Debug_init();
  pins::Init();
}

void loop() {
  for (size_t i = 0; i < transmitter_count; ++i) {
    const String msg = "From HSerial" + (String)(i + 1);
    transmitters_h[i].Send(msg);
  }
  delay(100);
}
