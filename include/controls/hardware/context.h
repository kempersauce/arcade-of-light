#pragma once

#include <memory>  // For shared_ptr

#include "controls/button.h"  // For Button

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
