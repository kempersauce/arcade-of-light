#pragma once

#include "controls/button.h"  // For Button

#include <memory>  // For shared_ptr

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
