#pragma once

#include <memory>  // for shared_ptr

#include "controls/button.h"  // for Button

namespace kss {
namespace controls {
namespace hardware {

class Context {
 public:
  virtual void PollAll();
};

}  // namespace hardware
}  // namespace controls
}  // namespace kss
