#include <HardwareSerial.h>  // for HardwareSerial

#include "serial/debug.h"          // for Debug
#include "serial/transmitter.h"  // for Transmitter

using namespace kss::serial;

const String test_msg{"0123456789"};

Transmitter transmitter{&Serial1};

void setup() { Debug_init(); }

void loop() { transmitter.Send(test_msg); }
