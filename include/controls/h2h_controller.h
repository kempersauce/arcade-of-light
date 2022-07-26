#pragma once

#include <memory>  // for shared_ptr

#include "controls/button.h"  // for Button

namespace kss {
namespace controls {

struct H2HController {
  std::shared_ptr<Button> buttons[8];
};

}  // namespace controls
}  // naemspace kss
