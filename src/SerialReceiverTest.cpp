// #include <SerialFlash.h>  // for Serial

// #include <vector>

// #include "serial/debug.h"          // for debug::*
// #include "serial/receiver_bank.h"  // for ReceiverBank

// using namespace kss::serial;

// void ShowMessage(const char* message) {
//   debug::println((String) "callback(\"" + message + "\")");
// }

// // Serials we listen on
// const std::vector<HardwareSerial*> serials{
//     &Serial1, &Serial2, &Serial3, &Serial4, &Serial5, &Serial6, &Serial7};

// ReceiverBank receivers{ShowMessage, serials};

// void setup() {
//   debug::Init();
//   debug::println("Serial Started");
// }

// void loop() { receivers.ReadAll(); }
