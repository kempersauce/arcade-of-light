#pragma once

#include <HardwareSerial.h>  // for HardwareSerial

#include <functional>
#include <string>
#include <vector>

#include "serial/debug.h"     // for debug::*
#include "serial/receiver.h"  // for Receiver

namespace kss {
namespace serial {

class ReceiverBank {
  std::function<void(const char*)> callback;

  std::vector<Receiver> receivers;

 public:
  ReceiverBank(std::function<void(const char*)> callback,
               const std::vector<HardwareSerial*>& serials)
      : callback{std::move(callback)} {
    for (HardwareSerial* serial : serials) {
      receivers.emplace_back(serial);
    }
  }

  void ReadAll() {
    for (size_t i = 0; i < receivers.size(); ++i) {
      auto& receiver = receivers[i];
      receiver.ReceiveMessages();
      while (receiver.HasMessages()) {
        char output[kMessageBufferSize];
        receiver.GetNextMessage(output);
        Debug("Received msg on serial::Receiver[" + i + "]: \"" + output +
              "\"");
        callback(output);
      }
    }
  }
};

}  // namespace serial
}  // namespace kss
