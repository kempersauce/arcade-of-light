#pragma once

#include "controls/button.h"           // for Button
#include "controls/controller.h"       // for Controller
#include "controls/hardware/matrix.h"  // for Matrix
#include "pins/pin_setup.h"            // for Controllers, Buttons

namespace kss {
namespace controls {

namespace _rocket {
constexpr size_t kButtonCount{2};
constexpr uint32_t kIdleTimeoutMillis{30 * 1000};
}  // namespace _rocket

struct RocketController : public Controller<_rocket::kButtonCount> {
  Button* up = buttons[0];
  Button* reset = buttons[1];

  RocketController() : Controller() {}
  RocketController(Button* const up, Button* const reset)
      : Controller({up, reset}, _rocket::kIdleTimeoutMillis) {}

  RocketController(hardware::Matrix& context, const size_t ctl_no = 0)
      : Controller(
            {context.CreateButton(pins::Controllers[ctl_no], pins::Buttons[1]),
             context.CreateButton(pins::Controllers[ctl_no], pins::Buttons[0])},
            _rocket::kIdleTimeoutMillis) {}

  static RocketController CreateTest(hardware::Matrix& context,
                                     const size_t ctl_no = 0) {
    return {context.CreateButton(pins::Controllers[ctl_no], pins::Buttons[5]),
            context.CreateButton(pins::Controllers[ctl_no], pins::Buttons[4])};
  }
};

}  // namespace controls
}  // namespace kss
