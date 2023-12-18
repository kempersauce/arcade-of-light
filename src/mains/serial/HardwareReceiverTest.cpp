#include <HardwareSerial.h>  // for HardwareSerial

#include <vector>

#include "pins/pin_setup.h"        // for pins::Init()
#include "serial/debug.h"          // for Debug
#include "serial/receiver_bank.h"  // for Receiver
#include "time/now.h"              // for Now

using namespace kss;
using namespace kss::serial;

void ShowMessage(const char* message) {
  //   Debug("callback(\"" + message + "\")");
}

// Serials we listen on
const std::vector<HardwareSerial*> serials{
    &Serial1, &Serial2, &Serial3, &Serial4, &Serial5, &Serial6, &Serial7};

ReceiverBank receivers{ShowMessage, serials};

void setup() {
  Debug_init();
  pins::Init();
}

uint32_t next = 0;
void loop() {
  uint32_t now = time::Now();
  if (now >= next) {
    next = now + 1000;
    Debug("Loops brother t=" + now);
  }
  receivers.ReadAll();
}
