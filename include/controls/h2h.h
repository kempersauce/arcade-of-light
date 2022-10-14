#pragma once

#include "controls/button.h"           // for Button
#include "controls/controller.h"       // for Controller
#include "controls/hardware/matrix.h"  // for Matrix
#include "pins/pin_setup.h"            // for Controllers, Buttons

namespace kss {
namespace controls {

namespace _h2h {
constexpr size_t kButtonCount{8};
constexpr uint32_t kIdleTimeoutMillis{45 * 1000};
}  // namespace _h2h

struct H2HController : public Controller<_h2h::kButtonCount> {
  H2HController() : Controller() {}
  H2HController(Button* a, Button* b, Button* c, Button* d, Button* e,
                Button* f, Button* g, Button* h)
      : Controller({a, b, c, d, e, f, g, h}, _h2h::kIdleTimeoutMillis) {}

  static H2HController TeamA(hardware::Matrix& context) {
    return H2HController{
        // HW Controller 0
        context.CreateButton(pins::Controllers[0], pins::Buttons[1]),
        context.CreateButton(pins::Controllers[0], pins::Buttons[4]),
        context.CreateButton(pins::Controllers[0], pins::Buttons[3]),
        context.CreateButton(pins::Controllers[0], pins::Buttons[2]),

        // HW Controller 1
        context.CreateButton(pins::Controllers[1], pins::Buttons[1]),
        context.CreateButton(pins::Controllers[1], pins::Buttons[4]),
        context.CreateButton(pins::Controllers[1], pins::Buttons[3]),
        context.CreateButton(pins::Controllers[1], pins::Buttons[2])};
  }

  static H2HController TeamB(hardware::Matrix& context) {
    return H2HController{
        // HW Controller 3
        context.CreateButton(pins::Controllers[3], pins::Buttons[2]),
        context.CreateButton(pins::Controllers[3], pins::Buttons[3]),
        context.CreateButton(pins::Controllers[3], pins::Buttons[4]),
        context.CreateButton(pins::Controllers[3], pins::Buttons[1]),

        // HW Controller 2
        context.CreateButton(pins::Controllers[2], pins::Buttons[2]),
        context.CreateButton(pins::Controllers[2], pins::Buttons[3]),
        context.CreateButton(pins::Controllers[2], pins::Buttons[4]),
        context.CreateButton(pins::Controllers[2], pins::Buttons[1])};
  }

  static constexpr uint32_t BOOM_TIME{3 * 1000};
  bool IsBoomTimeA() const {
    if (buttons[0]->GetMillisHeld() > BOOM_TIME &&
        buttons[1]->GetMillisHeld() > BOOM_TIME &&
        buttons[2]->GetMillisHeld() > BOOM_TIME &&
        buttons[3]->GetMillisReleased() > BOOM_TIME &&
        buttons[4]->GetMillisReleased() > BOOM_TIME &&
        buttons[5]->GetMillisReleased() > BOOM_TIME &&
        buttons[6]->IsDepressing() &&
        buttons[7]->GetMillisReleased() > BOOM_TIME) {
      return true;
    }
    return false;
  }

  bool IsBoomTimeB() const {
    if (buttons[7]->GetMillisHeld() > BOOM_TIME &&
        buttons[6]->GetMillisHeld() > BOOM_TIME &&
        buttons[5]->GetMillisHeld() > BOOM_TIME &&
        buttons[4]->GetMillisReleased() > BOOM_TIME &&
        buttons[3]->GetMillisReleased() > BOOM_TIME &&
        buttons[2]->GetMillisReleased() > BOOM_TIME &&
        buttons[1]->IsDepressing() &&
        buttons[0]->GetMillisReleased() > BOOM_TIME) {
      return true;
    }
    return false;
  }
};

}  // namespace controls
}  // namespace kss
