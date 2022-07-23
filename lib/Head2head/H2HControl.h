#include <memory>  // For shared_ptr

#include "controls/button.h"

struct H2HControl {
  std::shared_ptr<kss::controls::Button> buttons[8];
};
