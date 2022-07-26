#pragma once

#include <memory>  // for shared_ptr

#include "controls/button.h"  // for Button

namespace kss {
namespace games {
namespace h2h {

struct Controller {
  std::shared_ptr<controls::Button> buttons[8];
};

}  // namespace h2h
}  // namespace games
}  // naemspace kss
