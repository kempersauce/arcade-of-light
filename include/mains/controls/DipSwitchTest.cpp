#include <Arduino.h>

#include "pins/pin_setup.h"
#include "serial/debug.h"  // for Debug

using namespace kss;

constexpr size_t dip_switch_count{4};

constexpr uint8_t dip_pins[dip_switch_count]{pins::Dips[0], pins::Dips[1],
                                             pins::Dips[2], pins::Dips[3]};

void setup() {
  Debug_init();
  pins::Init();

  Debug("ready 2 goooo");
}

void loop() {
  String msg = "Dips: [";
  for (auto pin : dip_pins) {
    msg += (String)digitalRead(pin);
  }
  Debug(msg + "] t=" + millis());
  delay(100);
}
