#pragma once

#include "controls/button.h"           // for Button
#include "controls/controller.h"       // for Controller
#include "controls/hardware/matrix.h"  // for Matrix
#include "pins/pin_setup.h"            // for Controllers, Buttons

namespace kss {
namespace controls {

namespace _dir_pad {
constexpr size_t kButtonCount{6};
constexpr uint32_t kIdleTimeoutMillis{60 * 1000};  // 1 minute idle timeout
// constexpr uint32_t kIdleTimeoutMillis{15 * 1000};  // 15 seconds for testing
}  // namespace _dir_pad

struct DirPad : public Controller<_dir_pad::kButtonCount> {
  Button* b = buttons[0];
  Button* a = buttons[1];
  Button* down = buttons[2];
  Button* left = buttons[3];
  Button* right = buttons[4];
  Button* up = buttons[5];

  DirPad() : Controller() {}
  DirPad(Button* b, Button* a, Button* down, Button* left, Button* right,
         Button* up)
      : Controller({b, a, down, left, right, up},
                   _dir_pad::kIdleTimeoutMillis) {}

  DirPad(hardware::Matrix& context, size_t ctl_no)
      : Controller(
            {context.CreateButton(pins::Controllers[ctl_no], pins::Buttons[0]),
             context.CreateButton(pins::Controllers[ctl_no], pins::Buttons[1]),
             context.CreateButton(pins::Controllers[ctl_no], pins::Buttons[2]),
             context.CreateButton(pins::Controllers[ctl_no], pins::Buttons[3]),
             context.CreateButton(pins::Controllers[ctl_no], pins::Buttons[4]),
             context.CreateButton(pins::Controllers[ctl_no], pins::Buttons[5])},
            _dir_pad::kIdleTimeoutMillis) {
    exclude_from_idle.push_back(up);
  }
};

}  // namespace controls
}  // namespace kss
