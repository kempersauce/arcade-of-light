#include <Arduino.h>
#include <HardwareSerial.h>  // for HardwareSerial
#include <SPI.h>
#include <Wire.h>

#include <vector>

#include "pins/pin_setup.h"        // for pins::Init()
#include "serial/debug.h"          // for Debug
#include "serial/receiver_bank.h"  // for Receiver
#include "time/now.h"              // for Now
#include "time/soft_wait.h"        // for SOFT_WAIT

using namespace kss;
using namespace kss::serial;

void ShowMessage(const char* message) { Debug("callback(\"%s\")", message); }

// Serials we listen on
const std::vector<HardwareSerial*> serials{
    &Serial1, &Serial2, &Serial3, &Serial4, &Serial5, &Serial6, &Serial7};

ReceiverBank receivers{ShowMessage, serials};

void setup() {
  Debug_init();
  pins::Init();
  time::Init();
}

void loop() {
  SOFT_WAIT(1000) { Debug("Loops brother t=" + time::Now()); }
  receivers.ReadAll();
}
