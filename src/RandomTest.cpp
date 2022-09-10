// #include <Arduino.h>

// #include "controls/button.h"           // for Button
// #include "controls/hardware/matrix.h"  // for Matrix
// #include "math/random.h"               // for random::*
// #include "serial/debug.h"              // for debug::*

// using namespace kss;
// using namespace kss::engines;

// controls::hardware::Matrix controller;

// controls::Button* but1 = controller.CreateButton(2, 8);
// controls::Button* but2 = controller.CreateButton(2, 9);
// controls::Button* but3 = controller.CreateButton(2, 10);
// controls::Button* but4 = controller.CreateButton(2, 11);
// controls::Button* but5 = controller.CreateButton(2, 12);
// controls::Button* but6 = controller.CreateButton(2, 13);

// // Serials we listen on

// void setup() {
//   debug::Init();
// }

// void loop() {
//   controller.PollAll();

//   //   if (but1->IsDepressing()) {
//   //     Debug("Int16()=" + random::Int16());
//   //   }
//   if (but2->IsDepressing()) {
//     Debug("Int16()=" + random::Int16());
//   }
//   if (but3->IsDepressing()) {
//     Debug("Int16(10)=" + random::Int16(10));
//   }
//   if (but4->IsDepressing()) {
//     Debug("Int16(10, 20)=" + random::Int16(10, 20));
//   }
//   if (but5->IsDepressing()) {
//     Debug("Int16_incl(10)=" + random::Int16_incl(10));
//   }
//   if (but6->IsDepressing()) {
//     Debug("Int16_incl(10, 20)=" + random::Int16_incl(10, 20));
//   }

//   delay(7);
// }
