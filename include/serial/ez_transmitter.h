#pragma once

#include <EasyTransfer.h>  // for EasyTransfer

#include "serial/constants.h"  // for kBaudRate

namespace kss {
namespace serial {

template <typename SEND_DATA_STRUCTURE>
class EZTransmitter {
  // create object
  EasyTransfer ET;

  // give a name to the group of data
  SEND_DATA_STRUCTURE outgoing;

 public:
  EZTransmitter(HardwareSerial* serial) {
    serial->begin(kBaudRate);
    ET.begin(details(outgoing), serial);
  }

  void Send(SEND_DATA_STRUCTURE& msg) {
    outgoing = msg;
    ET.sendData();
  }
};

}  // namespace serial
}  // namespace kss
