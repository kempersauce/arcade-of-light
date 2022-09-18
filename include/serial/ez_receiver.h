#pragma once

#include <EasyTransfer.h>  // for EasyTransfer

#include <queue>  // for std::queue

#include "serial/constants.h"  // for kBaudRate

namespace kss {
namespace serial {

template <typename RECEIVE_DATA_STRUCTURE>
class EZReceiver {
 public:
  // create object
  EasyTransfer ET;

  // give a name to the group of data
  RECEIVE_DATA_STRUCTURE incoming;

  std::queue<RECEIVE_DATA_STRUCTURE> inbox;

  EZReceiver(HardwareSerial* serial) {
    serial->begin(kBaudRate);
    // start the library, pass in the data details and the name of the serial
    // port. Can be Serial, Serial1, Serial2, etc.
    ET.begin(details(incoming), serial);
  }

  bool ReceiveMessages() {
    // check and see if a data packet has come in.
    if (ET.receiveData()) {
      inbox.push(incoming);
      return true;
    }
    return false;
  }

  bool GetNextMessage(RECEIVE_DATA_STRUCTURE& dest) {
    if (inbox.empty()) {
      return false;
    }
    dest = inbox.front();
    inbox.pop();
    return true;
  }
};

}  // namespace serial
}  // namespace kss
