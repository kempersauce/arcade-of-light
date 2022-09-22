#include <Arduino.h>

#include "controls/button.h"           // for Button
#include "controls/hardware/matrix.h"  // for Matrix
#include "math/random.h"               // for random::*
#include "pins/pin_setup.h"            // for pins::*
#include "serial/debug.h"              // for Debug

using namespace kss;
using namespace kss::math;

controls::hardware::Matrix control_context;

controls::Button* but1;
controls::Button* but2;
controls::Button* but3;
controls::Button* but4;
controls::Button* but5;
controls::Button* but6;

// Serials we listen on

void setup() {
  Debug_init();
  pins::Init();

  but1 = control_context.CreateButton(pins::Controllers[0], pins::Buttons[0]);
  but2 = control_context.CreateButton(pins::Controllers[0], pins::Buttons[1]);
  but3 = control_context.CreateButton(pins::Controllers[0], pins::Buttons[2]);
  but4 = control_context.CreateButton(pins::Controllers[0], pins::Buttons[3]);
  but5 = control_context.CreateButton(pins::Controllers[0], pins::Buttons[4]);
  but6 = control_context.CreateButton(pins::Controllers[0], pins::Buttons[5]);
}

void loop() {
  control_context.PollAll();

  //   if (but1->IsDepressing()) {
  //     Debug("Int16()=" + random::Int16());
  //   }
  if (but2->IsDepressing()) {
    Debug("Int16()=" + random::Int16());
  }
  if (but3->IsDepressing()) {
    Debug("Int16(10)=" + random::Int16(10));
  }
  if (but4->IsDepressing()) {
    Debug("Int16(10, 20)=" + random::Int16(10, 20));
  }
  if (but5->IsDepressing()) {
    Debug("Int16_incl(10)=" + random::Int16_incl(10));
  }
  if (but6->IsDepressing()) {
    Debug("Int16_incl(10, 20)=" + random::Int16_incl(10, 20));
  }

  Debug_var(random::Int16(500, 5000));

  delay(100);
}
