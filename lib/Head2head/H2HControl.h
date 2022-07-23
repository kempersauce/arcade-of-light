#include <button.h>

#include <memory>  // For shared_ptr

struct H2HControl {
  std::shared_ptr<kss::controls::Button> buttons[8];
};
