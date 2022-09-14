#include <HardwareSerial.h>  // for HardwareSerial

#include <vector>

#include "serial/debug.h"          // for Debug
#include "serial/receiver_bank.h"  // for Receiver

using namespace kss::serial;

void ShowMessage(const char* message) {
//   Debug("callback(\"" + message + "\")");
}

// Serials we listen on
const std::vector<HardwareSerial*> serials{&Serial1};

ReceiverBank receivers{ShowMessage, serials};

void setup() { Debug_init(); }

void loop() { receivers.ReadAll(); }
